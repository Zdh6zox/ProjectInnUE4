// Fill out your copyright notice in the Description page of Project Settings.


#include "SGraphNode_StateMachine.h"
#include "StateMachineGraphNode.h"
#include "StateMachineGraphNode_State.h"
#include "StateMachineGraphNode_Action.h"
#include "StateMachineGraphNode_Logic.h"
#include "StateMachineGraphNode_Transition.h"
#include "StateMachineEditorTypes.h"
#include "Widgets/SBoxPanel.h"
#include "Widgets/Images/SImage.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Layout/SBorder.h"
#include "Widgets/SToolTip.h"
#include "Widgets/Text/SInlineEditableTextBlock.h"
#include "SGraphPanel.h"
#include "KismetWidgets/Public/SLevelOfDetailBranchNode.h"
#include "NodeFactory.h"
#include "Data/State/TransitionData.h"


void SStateMachinePin::Construct(const FArguments& InArgs, UEdGraphPin* InPin)
{
	SGraphPinAI::Construct(SGraphPinAI::FArguments(), InPin);
}

FSlateColor SStateMachinePin::GetPinColor() const
{
	return FColor::White;
}


void SGraphNode_StateMachine::Construct(const FArguments& InArgs, UStateMachineGraphNode* InNode)
{
	SGraphNodeAI::Construct(SGraphNodeAI::FArguments(), InNode);
}

void SGraphNode_StateMachine::UpdateGraphNode()
{
	bDragMarkerVisible = false;
	InputPins.Empty();
	OutputPins.Empty();

	if (EnterActionsBox.IsValid())
	{
		EnterActionsBox->ClearChildren();
	}
	else
	{
		SAssignNew(EnterActionsBox, SVerticalBox);
	}

	if (ExitActionsBox.IsValid())
	{
		ExitActionsBox->ClearChildren();
	}
	else
	{
		SAssignNew(ExitActionsBox, SVerticalBox);
	}

	if (LogicsBox.IsValid())
	{
		LogicsBox->ClearChildren();
	}
	else
	{
		SAssignNew(LogicsBox, SVerticalBox);
	}

	// Reset variables that are going to be exposed, in case we are refreshing an already setup node.
	RightNodeBox.Reset();
	LeftNodeBox.Reset();
	SubNodes.Reset();
	OutputPinBox.Reset();

	UStateMachineGraphNode* smNode = Cast<UStateMachineGraphNode>(GraphNode);
	const bool bIsStateNode = Cast<UStateMachineGraphNode_State>(smNode);
	const bool bIsActionNode = Cast<UStateMachineGraphNode_Action>(smNode);
	const bool bIsLogicNode = Cast<UStateMachineGraphNode_Logic>(smNode);
	const bool bIsTransNode = Cast<UStateMachineGraphNode_Transition>(smNode);

	if (smNode && bIsStateNode)
	{
		for (int32 i = 0; i < smNode->EnterActions.Num(); i++)
		{
			if (smNode->EnterActions[i])
			{
				TSharedPtr<SGraphNode> NewNode = FNodeFactory::CreateNodeWidget(smNode->EnterActions[i]);
				if (OwnerGraphPanelPtr.IsValid())
				{
					NewNode->SetOwner(OwnerGraphPanelPtr.Pin().ToSharedRef());
					OwnerGraphPanelPtr.Pin()->AttachGraphEvents(NewNode);
				}
				AddEnterAction(NewNode);
				NewNode->UpdateGraphNode();
			}
		}

		for (int32 i = 0; i < smNode->ExitActions.Num(); i++)
		{
			if (smNode->ExitActions[i])
			{
				TSharedPtr<SGraphNode> NewNode = FNodeFactory::CreateNodeWidget(smNode->ExitActions[i]);
				if (OwnerGraphPanelPtr.IsValid())
				{
					NewNode->SetOwner(OwnerGraphPanelPtr.Pin().ToSharedRef());
					OwnerGraphPanelPtr.Pin()->AttachGraphEvents(NewNode);
				}
				AddExitAction(NewNode);
				NewNode->UpdateGraphNode();
			}
		}

		for (int32 i = 0; i < smNode->Logics.Num(); i++)
		{
			if (smNode->Logics[i])
			{
				TSharedPtr<SGraphNode> NewNode = FNodeFactory::CreateNodeWidget(smNode->Logics[i]);
				if (OwnerGraphPanelPtr.IsValid())
				{
					NewNode->SetOwner(OwnerGraphPanelPtr.Pin().ToSharedRef());
					OwnerGraphPanelPtr.Pin()->AttachGraphEvents(NewNode);
				}
				AddLogic(NewNode);
				NewNode->UpdateGraphNode();
			}
		}

		//for (int32 i = 0; i < smNode->Transitions.Num(); i++)
		//{
		//	if (smNode->Transitions[i])
		//	{
		//		TSharedPtr<SGraphNode> NewNode = FNodeFactory::CreateNodeWidget(smNode->Transitions[i]);
		//		if (OwnerGraphPanelPtr.IsValid())
		//		{
		//			NewNode->SetOwner(OwnerGraphPanelPtr.Pin().ToSharedRef());
		//			OwnerGraphPanelPtr.Pin()->AttachGraphEvents(NewNode);
		//		}
		//		AddTransition(NewNode);
		//		NewNode->UpdateGraphNode();
		//	}
		//}
	}

	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);
	TWeakPtr<SNodeTitle> WeakNodeTitle = NodeTitle;
	auto GetNodeTitlePlaceholderWidth = [WeakNodeTitle]() -> FOptionalSize
	{
		TSharedPtr<SNodeTitle> NodeTitlePin = WeakNodeTitle.Pin();
		const float DesiredWidth = (NodeTitlePin.IsValid()) ? NodeTitlePin->GetTitleSize().X : 0.0f;
		return FMath::Max(75.0f, DesiredWidth);
	};
	auto GetNodeTitlePlaceholderHeight = [WeakNodeTitle]() -> FOptionalSize
	{
		TSharedPtr<SNodeTitle> NodeTitlePin = WeakNodeTitle.Pin();
		const float DesiredHeight = (NodeTitlePin.IsValid()) ? NodeTitlePin->GetTitleSize().Y : 0.0f;
		return FMath::Max(22.0f, DesiredHeight);
	};

	const FMargin NodePadding = FMargin(2.0f);
	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);

	if (bIsTransNode)
	{
		this->GetOrAddSlot(ENodeZone::Center)
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Center)
		[
			SNew(SImage)
			.Image(FEditorStyle::GetBrush(TEXT("BTEditor.Graph.BTNode.Icon")))
		];

		UStateMachineGraphNode_Transition* transNode = Cast<UStateMachineGraphNode_Transition>(GraphNode);
		UTransitionData* transData = Cast<UTransitionData>(transNode->NodeInstance);
		return;
	}

	this->GetOrAddSlot(ENodeZone::Center)
        .HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
		    .Padding(0.0f)
		    .BorderBackgroundColor(FLinearColor(0.2f, 0.2f, 0.2f, 0.2f))
		    .OnMouseButtonDown(this, &SGraphNode_StateMachine::OnMouseDown)
		    [
				SNew(SOverlay)

				// Pins and node details
		        + SOverlay::Slot()
		        .HAlign(HAlign_Fill)
		        .VAlign(VAlign_Fill)
		        [
					SNew(SVerticalBox)
					// INPUT PIN AREA
					+SVerticalBox::Slot()
					.AutoHeight()
		            [
			            SNew(SBox)
			            .MinDesiredHeight(NodePadding.Top)
		                [
			                SAssignNew(LeftNodeBox, SVerticalBox)
		                ]
		            ]

	                //Name
	                + SVerticalBox::Slot()
		            .Padding(FMargin(NodePadding.Left, 0.0f, NodePadding.Right, 0.0f))
					[
						SNew(SVerticalBox)
						+ SVerticalBox::Slot()
                        .AutoHeight()
						[
							SAssignNew(NodeBody, SBorder)
							.BorderImage(FEditorStyle::GetBrush("BTEditor.Graph.BTNode.Body"))
						    .BorderBackgroundColor(FLinearColor(0.5f, 0.5f, 0.5f, 0.1f))
						    .HAlign(HAlign_Fill)
						    .VAlign(VAlign_Center)
						    .Visibility(EVisibility::SelfHitTestInvisible)
						    [
								SNew(SOverlay)
								+ SOverlay::Slot()
		                        .HAlign(HAlign_Fill)
		                        .VAlign(VAlign_Fill)
		                        [
			                        SNew(SVerticalBox)
									+ SVerticalBox::Slot()
		                            .AutoHeight()
		                           [
			                           SNew(SHorizontalBox)
									   + SHorizontalBox::Slot()
		                               .AutoWidth()
		                               [
										   SNew(SLevelOfDetailBranchNode)
										   .UseLowDetailSlot(false)
		                                   .LowDetail()
		                                   [
											   SNew(SBox)
											   .WidthOverride_Lambda(GetNodeTitlePlaceholderWidth)
		                                       .HeightOverride_Lambda(GetNodeTitlePlaceholderHeight)
										   ]
	                                       .HighDetail()
										   [
											   SNew(SHorizontalBox)
											   //+ SHorizontalBox::Slot()
											   //.AutoWidth()
											   //.VAlign(VAlign_Center)
											   //[
												  // SNew(SImage)
												  // .Image(this, &SGraphNode_BehaviorTree::GetNameIcon)
											   //]
										       + SHorizontalBox::Slot()
											   .Padding(FMargin(4.0f, 0.0f, 4.0f, 0.0f))
											   [
												   SNew(SVerticalBox)
												   + SVerticalBox::Slot()
											       .AutoHeight()
											       [
												       SAssignNew(InlineEditableText, SInlineEditableTextBlock)
												       .Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
											           .Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
											           .OnVerifyTextChanged(this, &SGraphNode_StateMachine::OnVerifyNameTextChanged)
											           .OnTextCommitted(this, &SGraphNode_StateMachine::OnNameTextCommited)
											           .IsReadOnly(this, &SGraphNode_StateMachine::IsNameReadOnly)
											           .IsSelected(this, &SGraphNode_StateMachine::IsSelectedExclusively)
											       ]
										           + SVerticalBox::Slot()
											       .AutoHeight()
											       [
												       NodeTitle.ToSharedRef()
											       ]
											   ]
										   ]
									   ]
								   ]
							    ]
							]
						]
					]
		            // OUTPUT PIN AREA
		            + SVerticalBox::Slot()
			        .AutoHeight()
			        [
				       SNew(SBox)
				       .MinDesiredHeight(NodePadding.Bottom)
			           [
				            SAssignNew(RightNodeBox, SVerticalBox)
						    + SVerticalBox::Slot()
						    .HAlign(HAlign_Fill)
						    .VAlign(VAlign_Fill)
						    //.Padding(20.0f, 0.0f)
						    .FillHeight(1.0f)
						    [
							     SAssignNew(OutputPinBox, SHorizontalBox)
						    ]
			           ]
				   ]
				]

				// Drag marker overlay
				+ SOverlay::Slot()
			    .HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				[
					SNew(SBorder)
					.BorderBackgroundColor(FLinearColor(1.0f, 1.0f, 0.2f))
					.ColorAndOpacity(FLinearColor(1.0f, 1.0f, 0.2f))
					.BorderImage(FEditorStyle::GetBrush("BTEditor.Graph.BTNode.Body"))
					.Visibility(this,&SGraphNode_StateMachine::GetDragOverMarkerVisibility)
					[
						SNew(SBox)
						.HeightOverride(4)
					]
				]
				+SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
					.Padding(0.0f)
					.BorderBackgroundColor(FLinearColor(0.2f, 0.2f, 0.2f, 0.2f))
					.OnMouseButtonDown(this, &SGraphNode_StateMachine::OnMouseDown)
					[
						EnterActionsBox.ToSharedRef()
					]
				]
				+ SOverlay::Slot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Top)
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
					.Padding(0.0f)
					.BorderBackgroundColor(FLinearColor(0.2f, 0.2f, 0.2f, 0.2f))
					.OnMouseButtonDown(this, &SGraphNode_StateMachine::OnMouseDown)
					[
						ExitActionsBox.ToSharedRef()
					]
				]
				+ SOverlay::Slot()
					.HAlign(HAlign_Fill)
					.VAlign(VAlign_Top)
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
					.Padding(0.0f)
					.BorderBackgroundColor(FLinearColor(0.2f, 0.2f, 0.2f, 0.2f))
					.OnMouseButtonDown(this, &SGraphNode_StateMachine::OnMouseDown)
					[
						LogicsBox.ToSharedRef()
					]
				]
			]
		];

	CreatePinWidgets();
}

void SGraphNode_StateMachine::CreatePinWidgets()
{
	UStateMachineGraphNode* StateNode = CastChecked<UStateMachineGraphNode>(GraphNode);

	for (int32 PinIdx = 0; PinIdx < StateNode->Pins.Num(); PinIdx++)
	{
		UEdGraphPin* MyPin = StateNode->Pins[PinIdx];
		if (!MyPin->bHidden)
		{
			TSharedPtr<SGraphPin> NewPin = SNew(SStateMachinePin, MyPin)
				.ToolTipText(this, &SGraphNode_StateMachine::GetPinTooltip, MyPin);

			AddPin(NewPin.ToSharedRef());
		}
	}
}

EVisibility SGraphNode_StateMachine::GetNameVisibility() const
{
	UStateMachineGraphNode* smNode = Cast<UStateMachineGraphNode>(GraphNode);
	bool bIsTransNode = Cast<UStateMachineGraphNode_Transition>(smNode);
	return bIsTransNode ? EVisibility::Collapsed : EVisibility::Visible;
}

FText SGraphNode_StateMachine::GetPinTooltip(UEdGraphPin* GraphPinObj) const
{
	return FText::FromString("State");
}

void SGraphNode_StateMachine::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));

	const UEdGraphPin* PinObj = PinToAdd->GetPinObj();
	const bool bAdvancedParameter = PinObj && PinObj->bAdvancedView;
	if (bAdvancedParameter)
	{
		PinToAdd->SetVisibility(TAttribute<EVisibility>(PinToAdd, &SGraphPin::IsPinVisibleAsAdvanced));
	}

	if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
	{
		LeftNodeBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			.Padding(20.0f, 0.0f)
			[
				PinToAdd
			];
		InputPins.Add(PinToAdd);
	}
	else // Direction == EEdGraphPinDirection::EGPD_Output
	{
		const bool bIsSingleTaskPin = PinObj && (PinObj->PinType.PinCategory == UStateMachineEditorTypes::PinCategory_StateNode);
		if (bIsSingleTaskPin)
		{
			OutputPinBox->AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillWidth(1.0f)
				.Padding(20.0f, 0.0f)
				[
					PinToAdd
				];
		}
		else
		{
			OutputPinBox->AddSlot()
				.HAlign(HAlign_Fill)
				.VAlign(VAlign_Fill)
				.FillWidth(1.0f)
				[
					PinToAdd
				];
		}
		OutputPins.Add(PinToAdd);
	}
}

TSharedPtr<SToolTip> SGraphNode_StateMachine::GetComplexTooltip()
{
	return NULL;
}

void SGraphNode_StateMachine::GetOverlayBrushes(bool bSelected, const FVector2D WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const
{

}

TArray<FOverlayWidgetInfo> SGraphNode_StateMachine::GetOverlayWidgets(bool bSelected, const FVector2D& WidgetSize) const
{
	TArray<FOverlayWidgetInfo> Widgets;

	return Widgets;
}

TSharedRef<SGraphNode> SGraphNode_StateMachine::GetNodeUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent)
{
	TSharedPtr<SGraphNode> SubNode = GetSubNodeUnderCursor(MyGeometry, MouseEvent);
	return SubNode.IsValid() ? SubNode.ToSharedRef() : StaticCastSharedRef<SGraphNode>(AsShared());
}

void SGraphNode_StateMachine::MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter)
{
	SGraphNodeAI::MoveTo(NewPosition, NodeFilter);

	//// keep node order (defined by linked pins) up to date with actual positions
	//// this function will keep spamming on every mouse move update
	//UBehaviorTreeGraphNode* BTGraphNode = Cast<UBehaviorTreeGraphNode>(GraphNode);
	//if (BTGraphNode && !BTGraphNode->IsSubNode())
	//{
	//	UBehaviorTreeGraph* BTGraph = BTGraphNode->GetBehaviorTreeGraph();
	//	if (BTGraph)
	//	{
	//		for (int32 Idx = 0; Idx < BTGraphNode->Pins.Num(); Idx++)
	//		{
	//			UEdGraphPin* Pin = BTGraphNode->Pins[Idx];
	//			if (Pin && Pin->Direction == EGPD_Input && Pin->LinkedTo.Num() == 1)
	//			{
	//				UEdGraphPin* ParentPin = Pin->LinkedTo[0];
	//				if (ParentPin)
	//				{
	//					BTGraph->RebuildChildOrder(ParentPin->GetOwningNode());
	//				}
	//			}
	//		}
	//	}
	//}
}

void SGraphNode_StateMachine::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SGraphNode::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
}

void SGraphNode_StateMachine::AddEnterAction(TSharedPtr<SGraphNode> ActionWidget)
{
	EnterActionsBox->AddSlot().AutoHeight()
		[
			ActionWidget.ToSharedRef()
		];

	EnterActionWidgets.Add(ActionWidget);
	AddSubNode(ActionWidget);
}

void SGraphNode_StateMachine::AddExitAction(TSharedPtr<SGraphNode> ActionWidget)
{
	ExitActionsBox->AddSlot().AutoHeight()
		[
			ActionWidget.ToSharedRef()
		];

	ExitActionWidgets.Add(ActionWidget);
	AddSubNode(ActionWidget);
}

void SGraphNode_StateMachine::AddLogic(TSharedPtr<SGraphNode> LogicWidget)
{
	LogicsBox->AddSlot().AutoHeight()
		[
			LogicWidget.ToSharedRef()
		];

	LogicWidgets.Add(LogicWidget);
	AddSubNode(LogicWidget);
}

//void SGraphNode_StateMachine::AddTransition(TSharedPtr<SGraphNode> TransWidget)
//{
//	TransWidgets.Add(TransWidget);
//	AddSubNode(TransWidget);
//}
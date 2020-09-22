// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineEditor.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "WorkflowOrientedApp/WorkflowTabFactory.h"
#include "Widgets/Input/SButton.h"
#include "StateMachineEditorTabFactories.h"
#include "GraphEditor.h"
#include "GraphEditorActions.h"
#include "IDetailsView.h"
#include "Data/StateMachineData.h"
#include "StateMachineEditorModule.h"
#include "StateMachineEditorMode.h"
#include "StateMachineDataGraph.h"
#include "StateMachineGraphNode_State.h"
#include "StateMachineGraphNode_Action.h"
#include "StateMachineGraphNode_Logic.h"
#include "StateMachineGraphNode_Transition.h"
#include "EdGraphSchema_StateMachineData.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Widgets/Docking/SDockTab.h"

#define LOCTEXT_NAMESPACE "StateMachineEditor"

FStateMachineEditor::FStateMachineEditor()
{
	StateMachineData = nullptr;
	OnPackageSavedDelegateHandle = UPackage::PackageSavedEvent.AddRaw(this, &FStateMachineEditor::OnPackageSaved);
}

FStateMachineEditor::~FStateMachineEditor()
{
	UPackage::PackageSavedEvent.Remove(OnPackageSavedDelegateHandle);
}

FName FStateMachineEditor::GetToolkitFName() const
{
	return FName("State Machine");
}

FText FStateMachineEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "StateMachine");
}

FString FStateMachineEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "StateMachine ").ToString();
}

FLinearColor FStateMachineEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0, 0, 1.0f);
}

FText FStateMachineEditor::GetToolkitName() const
{
	const UObject* EditingObject = StateMachineData;
	if (EditingObject != nullptr)
	{
		return FAssetEditorToolkit::GetLabelForObject(EditingObject);
	}

	return FText();
}

FText FStateMachineEditor::GetToolkitToolTipText() const
{
	const UObject* EditingObject = StateMachineData;
	if (EditingObject != nullptr)
	{
		return FAssetEditorToolkit::GetToolTipTextForObject(EditingObject);
	}

	return FText();
}

void FStateMachineEditor::InitStateMachineEditor(const EToolkitMode::Type Mode, const TSharedPtr<class IToolkitHost>& InitToolkitHost, UObject* InObject)
{
	TSharedPtr<FStateMachineEditor> ThisPtr(SharedThis(this));
	if (!DocumentManager.IsValid())
	{
		DocumentManager = MakeShareable(new FDocumentTracker);
		DocumentManager->Initialize(ThisPtr);

		// Register the document factories
		{
			TSharedRef<FDocumentTabFactory> GraphEditorFactory = MakeShareable(new FSMGraphEditorSummoner(ThisPtr,
				FSMGraphEditorSummoner::FOnCreateGraphEditorWidget::CreateSP(this, &FStateMachineEditor::CreateGraphEditorWidget)
			));

			// Also store off a reference to the grapheditor factory so we can find all the tabs spawned by it later.
			GraphEditorTabFactoryPtr = GraphEditorFactory;
			DocumentManager->RegisterDocumentFactory(GraphEditorFactory);
		}
	}

	FGraphEditorCommands::Register();
	//FBTCommonCommands::Register();
	//FBTDebuggerCommands::Register();
	//FBTBlackboardCommands::Register();

	const TSharedRef<FTabManager::FLayout> DummyLayout = FTabManager::NewLayout("NullLayout")->AddArea(FTabManager::NewPrimaryArea());
	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;
	InitAssetEditor(Mode, InitToolkitHost, FStateMachineEditorModule::StateMachineEditorAppIdentifier, DummyLayout, bCreateDefaultStandaloneMenu, bCreateDefaultToolbar, InObject);

	//ToolkitCommands->MapAction(FBTCommonCommands::Get().SearchBT,
	//	FExecuteAction::CreateSP(this, &FBehaviorTreeEditor::SearchTree),
	//	FCanExecuteAction::CreateSP(this, &FBehaviorTreeEditor::CanSearchTree)
	//);

	//ToolkitCommands->MapAction(FBTCommonCommands::Get().NewBlackboard,
	//	FExecuteAction::CreateSP(this, &FBehaviorTreeEditor::CreateNewBlackboard),
	//	FCanExecuteAction::CreateSP(this, &FBehaviorTreeEditor::CanCreateNewBlackboard)
	//);
	//ExtendMenu();
	CreateInternalWidgets();

	//Debugger = MakeShareable(new FBehaviorTreeDebugger);
	//Debugger->Setup(BehaviorTree, SharedThis(this));
	//Debugger->OnDebuggedBlackboardChanged().AddSP(this, &FBehaviorTreeEditor::HandleDebuggedBlackboardChanged);
	//BindDebuggerToolbarCommands();

	//FStateMachineEditorModule& SMEditorModule = FModuleManager::LoadModuleChecked<FStateMachineEditorModule>("StateMachineEditorModule");
	//AddMenuExtender(SMEditorModule.GetMenuExtensibilityManager()->GetAllExtenders(GetToolkitCommands(), GetEditingObjects()));

	AddApplicationMode("StateMachineData", MakeShareable(new FStateMachineEditorApplicationMode(SharedThis(this))));

	//BlackboardEditor = SNew(SBehaviorTreeBlackboardEditor, GetToolkitCommands(), GetBlackboardData())
	//	.OnEntrySelected(this, &FBehaviorTreeEditor::HandleBlackboardEntrySelected)
	//	.OnGetDebugKeyValue(this, &FBehaviorTreeEditor::HandleGetDebugKeyValue)
	//	.OnIsDebuggerReady(this, &FBehaviorTreeEditor::IsDebuggerReady)
	//	.OnIsDebuggerPaused(this, &FBehaviorTreeEditor::IsDebuggerPaused)
	//	.OnGetDebugTimeStamp(this, &FBehaviorTreeEditor::HandleGetDebugTimeStamp)
	//	.OnGetDisplayCurrentState(this, &FBehaviorTreeEditor::HandleGetDisplayCurrentState)
	//	.OnBlackboardKeyChanged(this, &FBehaviorTreeEditor::HandleBlackboardKeyChanged)
	//	.OnIsBlackboardModeActive(this, &FBehaviorTreeEditor::HandleIsBlackboardModeActive);

	UStateMachineData* smDataToEdit = Cast<UStateMachineData>(InObject);

	StateMachineData = smDataToEdit;

	if (smDataToEdit != nullptr)
	{
		SetCurrentMode("StateMachineData");
	}

	OnClassListUpdated();
	RegenerateMenusAndToolbars();
}

void FStateMachineEditor::CreateInternalWidgets()
{
	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false);
	DetailsViewArgs.NotifyHook = this;
	DetailsViewArgs.DefaultsOnlyVisibility = EEditDefaultsOnlyNodeVisibility::Hide;
	DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObject(NULL);
	DetailsView->SetIsPropertyEditingEnabledDelegate(FIsPropertyEditingEnabled::CreateSP(this, &FStateMachineEditor::IsPropertyEditable));
	DetailsView->OnFinishedChangingProperties().AddSP(this, &FStateMachineEditor::OnFinishedChangingProperties);
}

TSharedRef<class SGraphEditor> FStateMachineEditor::CreateGraphEditorWidget(UEdGraph* InGraph)
{
	check(InGraph != NULL);

	if (!GraphEditorCommands.IsValid())
	{
		CreateCommandList();

		GraphEditorCommands->MapAction(FGraphEditorCommands::Get().RemoveExecutionPin,
			FExecuteAction::CreateSP(this, &FStateMachineEditor::OnRemoveInputPin),
			FCanExecuteAction::CreateSP(this, &FStateMachineEditor::CanRemoveInputPin)
		);

		GraphEditorCommands->MapAction(FGraphEditorCommands::Get().AddExecutionPin,
			FExecuteAction::CreateSP(this, &FStateMachineEditor::OnAddInputPin),
			FCanExecuteAction::CreateSP(this, &FStateMachineEditor::CanAddInputPin)
		);
	}

	SGraphEditor::FGraphEditorEvents InEvents;
	InEvents.OnSelectionChanged = SGraphEditor::FOnSelectionChanged::CreateSP(this, &FStateMachineEditor::OnSelectedNodesChanged);
	InEvents.OnNodeDoubleClicked = FSingleNodeEvent::CreateSP(this, &FStateMachineEditor::OnNodeDoubleClicked);
	InEvents.OnTextCommitted = FOnNodeTextCommitted::CreateSP(this, &FStateMachineEditor::OnNodeTitleCommitted);

	// Make title bar
	TSharedRef<SWidget> TitleBarWidget =
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush(TEXT("Graph.TitleBackground")))
		.HAlign(HAlign_Fill)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.HAlign(HAlign_Center)
		.FillWidth(1.f)
		[
			SNew(STextBlock)
			.Text(FText::FromString("StateMachineGraph"))
		.TextStyle(FEditorStyle::Get(), TEXT("GraphBreadcrumbButtonText"))
		]
		];

	// Make full graph editor
	const bool bGraphIsEditable = InGraph->bEditable;
	return SNew(SGraphEditor)
		.AdditionalCommands(GraphEditorCommands)
		.IsEditable(this, &FStateMachineEditor::InEditingMode, bGraphIsEditable)
		.Appearance(this, &FStateMachineEditor::GetGraphAppearance)
		.TitleBar(TitleBarWidget)
		.GraphToEdit(InGraph)
		.GraphEvents(InEvents);
}

bool FStateMachineEditor::IsPropertyEditable() const
{
	return true;
}

void FStateMachineEditor::OnPackageSaved(const FString& PackageFileName, UObject* Outer)
{
	UStateMachineDataGraph* MyGraph = StateMachineData ? Cast<UStateMachineDataGraph>(StateMachineData->SMGraph) : NULL;
	if (MyGraph)
	{
		MyGraph->UpdateAsset(UStateMachineDataGraph::ClearDebuggerFlags);
	}
}

void FStateMachineEditor::OnFinishedChangingProperties(const FPropertyChangedEvent& PropertyChangedEvent)
{
	StateMachineData->SMGraph->GetSchema()->ForceVisualizationCacheClear();
}

void FStateMachineEditor::OnSelectedNodesChanged(const TSet<class UObject *>& NewSelection)
{
	TArray<UObject*> Selection;

	for (UObject* SelectionEntry : NewSelection)
	{
		UStateMachineGraphNode_State* stateNode = Cast<UStateMachineGraphNode_State>(SelectionEntry);
		if (stateNode != nullptr)
		{
			Selection.Add(stateNode->NodeInstance);
		}

		UStateMachineGraphNode_Action* actionNode = Cast<UStateMachineGraphNode_Action>(SelectionEntry);
		if (actionNode != nullptr)
		{
			Selection.Add(actionNode->NodeInstance);
		}

		UStateMachineGraphNode_Logic* logicNode = Cast<UStateMachineGraphNode_Logic>(SelectionEntry);
		if (logicNode != nullptr)
		{
			Selection.Add(logicNode->NodeInstance);
		}

		UStateMachineGraphNode_Transition* transitionNode = Cast<UStateMachineGraphNode_Transition>(SelectionEntry);
		if (transitionNode != nullptr)
		{
			Selection.Add(transitionNode->NodeInstance);
		}
	}

	if (DetailsView.IsValid())
	{
		if (Selection.Num() >= 1)
		{
			DetailsView->SetObjects(Selection);
		}
		else
		{
			DetailsView->SetObject(StateMachineData);
		}
	}
}

void FStateMachineEditor::OnNodeDoubleClicked(class UEdGraphNode* Node)
{

}

void FStateMachineEditor::OnNodeTitleCommitted(const FText& NewText, ETextCommit::Type CommitInfo, UEdGraphNode* NodeBeingChanged)
{

}

bool FStateMachineEditor::InEditingMode(bool bGraphIsEditable) const
{
	return bGraphIsEditable;
}

FGraphAppearanceInfo FStateMachineEditor::GetGraphAppearance() const
{
	FGraphAppearanceInfo AppearanceInfo;
	AppearanceInfo.CornerText = FText::FromString("StateMachine Data");

	//const int32 StepIdx = Debugger.IsValid() ? Debugger->GetShownStateIndex() : 0;
	//if (Debugger.IsValid() && !Debugger->IsDebuggerRunning())
	//{
	//	AppearanceInfo.PIENotifyText = FText::FromString("Inactive");
	//}
	//else if (StepIdx)
	//{
	//	AppearanceInfo.PIENotifyText = FText::FromString("StepsBack");
	//}

	return AppearanceInfo;
}

void FStateMachineEditor::OnAddInputPin()
{

}

void FStateMachineEditor::OnRemoveInputPin()
{

}

bool FStateMachineEditor::CanAddInputPin() const
{
	return false;
}

bool FStateMachineEditor::CanRemoveInputPin() const
{
	return false;
}

void FStateMachineEditor::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, UProperty* PropertyThatChanged)
{
}

void FStateMachineEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& InTabManager)
{
	DocumentManager->SetTabManager(InTabManager);

	FWorkflowCentricApplication::RegisterTabSpawners(InTabManager);
}


void FStateMachineEditor::RegisterToolbarTab(const TSharedRef<class FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);
}

TSharedRef<SWidget> FStateMachineEditor::SpawnProperties()
{
	//return 	SNew(SButton)
	//	.VAlign(VAlign_Center)
	//	.HAlign(HAlign_Center)
	//	.Text(FText::FromString("TEST"));

	return
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.0f)
		.HAlign(HAlign_Fill)
		[
			DetailsView.ToSharedRef()
		];
	//+ SVerticalBox::Slot()
	//	.AutoHeight()
	//	.HAlign(HAlign_Left)
	//	.VAlign(VAlign_Top)
	//	[
	//		SNew(SVerticalBox)
	//		+ SVerticalBox::Slot()
	//	.HAlign(HAlign_Fill)
	//	.Padding(0.0f, 5.0f)
	//	[
	//		SNew(SBorder)
	//		.BorderBackgroundColor(FLinearColor(0.0f, 0.02f, 0.1f))
	//	.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
	//	.Padding(FMargin(5.0f))
	//	[
	//		SNew(STextBlock)
	//		.Text(FText::FromString("Test1"))
	//	]
	//	]
	//+ SVerticalBox::Slot()
	//	.HAlign(HAlign_Fill)
	//	.Padding(0.0f, 5.0f)
	//	[
	//		SNew(SBorder)
	//		.BorderBackgroundColor(FLinearColor(0.0f, 0.02f, 0.1f))
	//	.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
	//	.Padding(FMargin(5.0f))
	//	[
	//		SNew(STextBlock)
	//		.Text(FText::FromString("Test2"))
	//	]
	//	]
	//+ SVerticalBox::Slot()
	//	.HAlign(HAlign_Fill)
	//	.Padding(0.0f, 5.0f)
	//	[
	//		SNew(SBorder)
	//		.BorderBackgroundColor(FLinearColor(0.0f, 0.22f, 0.4f))
	//	.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
	//	.Padding(FMargin(5.0f))
	//	[
	//		SNew(STextBlock)
	//		.Text(FText::FromString("Test3"))
	//	]
	//	]
	//+ SVerticalBox::Slot()
	//	.HAlign(HAlign_Fill)
	//	.Padding(0.0f, 5.0f)
	//	[
	//		SNew(SBorder)
	//		.BorderBackgroundColor(FLinearColor(0.0f, 0.4f, 0.22f))
	//	.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
	//	.Padding(FMargin(5.0f))
	//	[
	//		SNew(STextBlock)
	//		.Text(FText::FromString("Test4"))
	//	]
	//	]
	//	];
		
}

void FStateMachineEditor::SaveAsset_Execute()
{
	if (StateMachineData)
	{
		UStateMachineDataGraph* smGraph = Cast<UStateMachineDataGraph>(StateMachineData->SMGraph);
		if (smGraph)
		{
			smGraph->OnSave();
		}
	}
	// save it
	FWorkflowCentricApplication::SaveAsset_Execute();
}

void FStateMachineEditor::RestoreStateMachine()
{
	// Update BT asset data based on saved graph to have correct data in editor
	UStateMachineDataGraph* MyGraph = Cast<UStateMachineDataGraph>(StateMachineData->SMGraph);
	const bool bNewGraph = MyGraph == NULL;
	if (MyGraph == NULL)
	{
		StateMachineData->SMGraph = FBlueprintEditorUtils::CreateNewGraph(StateMachineData, TEXT("StateMachineDataGraph"), UStateMachineDataGraph::StaticClass(), UEdGraphSchema_StateMachineData::StaticClass());
		MyGraph = Cast<UStateMachineDataGraph>(StateMachineData->SMGraph);

		//// Initialize the behavior tree graph
		//const UEdGraphSchema* Schema = MyGraph->GetSchema();
		//Schema->CreateDefaultNodesForGraph(*MyGraph);

		MyGraph->OnCreated();
	}
	else
	{
		MyGraph->OnLoaded();
	}

	MyGraph->Initialize();

	TSharedRef<FTabPayload_UObject> Payload = FTabPayload_UObject::Make(MyGraph);
	TSharedPtr<SDockTab> DocumentTab = DocumentManager->OpenDocument(Payload, bNewGraph ? FDocumentTracker::OpenNewDocument : FDocumentTracker::RestorePreviousDocument);

	if (StateMachineData->LastEditedDocuments.Num() > 0)
	{
		TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(DocumentTab->GetContent());
		GraphEditor->SetViewLocation(StateMachineData->LastEditedDocuments[0].SavedViewOffset, StateMachineData->LastEditedDocuments[0].SavedZoomAmount);
	}
}

void FStateMachineEditor::SaveEditedObjectState()
{
	// Clear currently edited documents
	StateMachineData->LastEditedDocuments.Empty();

	// Ask all open documents to save their state, which will update LastEditedDocuments
	DocumentManager->SaveAllState();
}

void FStateMachineEditor::OnGraphEditorFocused(const TSharedRef<SGraphEditor>& InGraphEditor)
{
	UpdateGraphEdPtr = InGraphEditor;
	//FocusedGraphOwner = Cast<UBehaviorTreeGraphNode_CompositeDecorator>(InGraphEditor->GetCurrentGraph()->GetOuter());

	FGraphPanelSelectionSet CurrentSelection;
	CurrentSelection = InGraphEditor->GetSelectedNodes();
	OnSelectedNodesChanged(CurrentSelection);
}

#undef LOCTEXT_NAMESPACE
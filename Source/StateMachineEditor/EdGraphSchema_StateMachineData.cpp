// Fill out your copyright notice in the Description page of Project Settings.


#include "EdGraphSchema_StateMachineData.h"
#include "StateMachineEditorTypes.h"
#include "StateMachineEditorModule.h"
#include "StateMachineGraphNode_State.h"
#include "StateMachineGraphNode_Action.h"
#include "StateMachineGraphNode_Logic.h"
#include "StateMachineGraphNode_Transition.h"
#include "SMEditorConnectionDrawingPolicy.h"
#include "Data/State/StateData.h"
#include "Data/State/TransitionData.h"
#include "Data/Action/ActionDataBase.h"
#include "Data/Logic/LogicDataBase.h"
#include "EdGraph/EdGraph.h"
#include "StateMachineDataGraph.h"
#include "ScopedTransaction.h"

#include "EdGraphUtilities.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Kismet2/BlueprintEditorUtils.h"

UEdGraphNode* FEdGraphSchemaSMAction_NewState::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode /* = true */)
{
	UEdGraphNode* ResultNode = NULL;

	// If there is a template, we actually use it
	if (NodeTemplate != NULL)
	{
		const FScopedTransaction Transaction(NSLOCTEXT("UnrealEd", "K2_AddNode", "Add Node"));
		ParentGraph->Modify();
		if (FromPin)
		{
			FromPin->Modify();
		}

		// set outer to be the graph so it doesn't go away
		NodeTemplate->Rename(NULL, ParentGraph);
		ParentGraph->AddNode(NodeTemplate, true, bSelectNewNode);

		NodeTemplate->CreateNewGuid();
		NodeTemplate->PostPlacedNewNode();
		NodeTemplate->AllocateDefaultPins();
		NodeTemplate->AutowireNewNode(FromPin);

		NodeTemplate->NodePosX = Location.X;
		NodeTemplate->NodePosY = Location.Y;
		//@TODO: ANIM: SNAP_GRID isn't centralized or exposed - NodeTemplate->SnapToGrid(SNAP_GRID);

		ResultNode = NodeTemplate;

		ResultNode->SetFlags(RF_Transactional);

		//UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraphChecked(ParentGraph);
		//FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);
	}

	return ResultNode;
}

void FEdGraphSchemaSMAction_NewState::AddReferencedObjects(FReferenceCollector& Collector)
{

}

int32 UEdGraphSchema_StateMachineData::CurrentCacheRefreshID = 0;

UEdGraphSchema_StateMachineData::UEdGraphSchema_StateMachineData(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UEdGraphSchema_StateMachineData::CreateDefaultNodesForGraph(UEdGraph& Graph) const
{
	//Do nothing
}

bool UEdGraphSchema_StateMachineData::CreateAutomaticConversionNodeAndConnections(UEdGraphPin* PinA, UEdGraphPin* PinB) const
{
	UStateMachineGraphNode_State* NodeA = Cast<UStateMachineGraphNode_State>(PinA->GetOwningNode());
	UStateMachineGraphNode_State* NodeB = Cast<UStateMachineGraphNode_State>(PinB->GetOwningNode());

	if ((NodeA != NULL) && (NodeB != NULL)
		&& (NodeA->GetInputPin() != NULL) && (NodeA->GetOutputPin() != NULL)
		&& (NodeB->GetInputPin() != NULL) && (NodeB->GetOutputPin() != NULL))
	{
		UStateMachineGraphNode_Transition* TransitionNode = FEdGraphSchemaSMAction_NewState::SpawnNodeFromTemplate<UStateMachineGraphNode_Transition>(NodeA->GetGraph(), NewObject<UStateMachineGraphNode_Transition>(), FVector2D(0.0f, 0.0f), false);

		//TSharedPtr<struct FGraphNodeClassHelper> TransitionClassCache = MakeShareable(new FGraphNodeClassHelper(UTransitionData::StaticClass()));
		UStateMachineDataGraph* outerGraph = Cast<UStateMachineDataGraph>(NodeA->GetGraph());
		if (outerGraph != NULL)
		{
			TransitionNode->NodeInstance = NewObject<UTransitionData>(outerGraph->GetOuter());
		}		

		if (PinA->Direction == EGPD_Output)
		{
			TransitionNode->CreateConnections(NodeA, NodeB);
			UStateData* stateData = Cast<UStateData>(NodeA->NodeInstance);
			stateData->Transitions.Add(Cast<UTransitionData>(TransitionNode->NodeInstance));
		}
		else
		{
			TransitionNode->CreateConnections(NodeB, NodeA);
			UStateData* stateData = Cast<UStateData>(NodeB->NodeInstance);
			stateData->Transitions.Add(Cast<UTransitionData>(TransitionNode->NodeInstance));
		}

		//UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraphChecked(TransitionNode->GetBoundGraph());
		//FBlueprintEditorUtils::MarkBlueprintAsStructurallyModified(Blueprint);

		return true;
	}

	return false;
}

void UEdGraphSchema_StateMachineData::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	const FName PinCategory = ContextMenuBuilder.FromPin ?
		ContextMenuBuilder.FromPin->PinType.PinCategory :
		UStateMachineEditorTypes::PinCategory_StateNode;

	const bool bNoParent = (ContextMenuBuilder.FromPin == NULL);
	const bool bNotState = !bNoParent;

	FStateMachineEditorModule& EditorModule = FModuleManager::GetModuleChecked<FStateMachineEditorModule>(TEXT("StateMachineEditorModule"));
	FGraphNodeClassHelper* ClassCache = EditorModule.GetStateClassCache().Get();

	FText text = FText::FromString("State");
	TArray<FGraphNodeClassData> NodeClasses;
	ClassCache->GatherClasses(UStateData::StaticClass(), NodeClasses);

	TSharedPtr<FEdGraphSchemaSMAction_NewState> NewStateNode(new FEdGraphSchemaSMAction_NewState(text, text, text, 0));
	UStateMachineGraphNode_State* OpNode = NewObject<UStateMachineGraphNode_State>(ContextMenuBuilder.OwnerOfTemporaries, UStateMachineGraphNode_State::StaticClass());
	OpNode->ClassData = NodeClasses[0];
	NewStateNode->NodeTemplate = OpNode;
	ContextMenuBuilder.AddAction(NewStateNode);
}

void UEdGraphSchema_StateMachineData::GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	Super::GetContextMenuActions(Menu, Context);
}

const FPinConnectionResponse UEdGraphSchema_StateMachineData::CanCreateConnection(const UEdGraphPin* PinA, const UEdGraphPin* PinB) const
{
	// Make sure the pins are not on the same node
	if (PinA->GetOwningNode() == PinB->GetOwningNode())
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Both are on the same node"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE_WITH_CONVERSION_NODE, TEXT("Connect nodes"));
}

const FPinConnectionResponse UEdGraphSchema_StateMachineData::CanMergeNodes(const UEdGraphNode* A, const UEdGraphNode* B) const
{
	return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT(""));
}

FLinearColor UEdGraphSchema_StateMachineData::GetPinTypeColor(const FEdGraphPinType& PinType) const
{
	return FColor::White;
}

FConnectionDrawingPolicy* UEdGraphSchema_StateMachineData::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const
{
	//return new FBehaviorTreeConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
	return new FSMEditorConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

bool UEdGraphSchema_StateMachineData::IsCacheVisualizationOutOfDate(int32 InVisualizationCacheID) const
{
	return CurrentCacheRefreshID != InVisualizationCacheID;
}

int32 UEdGraphSchema_StateMachineData::GetCurrentVisualizationCacheID() const
{
	return CurrentCacheRefreshID;
}

void UEdGraphSchema_StateMachineData::ForceVisualizationCacheClear() const
{
	++CurrentCacheRefreshID;
}

void UEdGraphSchema_StateMachineData::GetGraphNodeContextActions(FGraphContextMenuBuilder& ContextMenuBuilder, int32 SubNodeFlags) const
{
	//Super::GetGraphNodeContextActions(ContextMenuBuilder, SubNodeFlags);

	if (SubNodeFlags == EStateSubNode::EnterAction)
	{
		UClass* GraphNodeClass = nullptr;
		TArray<FGraphNodeClassData> NodeClasses;
		GetSubNodeClasses(SubNodeFlags, NodeClasses, GraphNodeClass);
		UEdGraph* Graph = (UEdGraph*)ContextMenuBuilder.CurrentGraph;

		for (const auto& NodeClass : NodeClasses)
		{
			const FText NodeTypeName = FText::FromString(FName::NameToDisplayString(NodeClass.ToString(), false));

			UStateMachineGraphNode_Action* OpNode = NewObject<UStateMachineGraphNode_Action>(Graph, GraphNodeClass);
			OpNode->IsEnterAction = true;
			OpNode->ClassData = NodeClass;

			TSharedPtr<FAISchemaAction_NewSubNode> AddOpAction = UAIGraphSchema::AddNewSubNodeAction(ContextMenuBuilder, NodeClass.GetCategory(), NodeTypeName, FText::GetEmpty());
			AddOpAction->ParentNode = Cast<UAIGraphNode>(ContextMenuBuilder.SelectedObjects[0]);
			AddOpAction->NodeTemplate = OpNode;
		}
	}
	else if (SubNodeFlags == EStateSubNode::ExitAction)
	{
		UClass* GraphNodeClass = nullptr;
		TArray<FGraphNodeClassData> NodeClasses;
		GetSubNodeClasses(SubNodeFlags, NodeClasses, GraphNodeClass);
		UEdGraph* Graph = (UEdGraph*)ContextMenuBuilder.CurrentGraph;

		for (const auto& NodeClass : NodeClasses)
		{
			const FText NodeTypeName = FText::FromString(FName::NameToDisplayString(NodeClass.ToString(), false));

			UStateMachineGraphNode_Action* OpNode = NewObject<UStateMachineGraphNode_Action>(Graph, GraphNodeClass);
			OpNode->IsEnterAction = false;
			OpNode->ClassData = NodeClass;

			TSharedPtr<FAISchemaAction_NewSubNode> AddOpAction = UAIGraphSchema::AddNewSubNodeAction(ContextMenuBuilder, NodeClass.GetCategory(), NodeTypeName, FText::GetEmpty());
			AddOpAction->ParentNode = Cast<UAIGraphNode>(ContextMenuBuilder.SelectedObjects[0]);
			AddOpAction->NodeTemplate = OpNode;
		}
	}
	else if (SubNodeFlags == EStateSubNode::Logic)
	{
		UClass* GraphNodeClass = nullptr;
		TArray<FGraphNodeClassData> NodeClasses;
		GetSubNodeClasses(SubNodeFlags, NodeClasses, GraphNodeClass);
		UEdGraph* Graph = (UEdGraph*)ContextMenuBuilder.CurrentGraph;

		for (const auto& NodeClass : NodeClasses)
		{
			const FText NodeTypeName = FText::FromString(FName::NameToDisplayString(NodeClass.ToString(), false));

			UStateMachineGraphNode_Logic* OpNode = NewObject<UStateMachineGraphNode_Logic>(Graph, GraphNodeClass);
			OpNode->ClassData = NodeClass;

			TSharedPtr<FAISchemaAction_NewSubNode> AddOpAction = UAIGraphSchema::AddNewSubNodeAction(ContextMenuBuilder, NodeClass.GetCategory(), NodeTypeName, FText::GetEmpty());
			AddOpAction->ParentNode = Cast<UAIGraphNode>(ContextMenuBuilder.SelectedObjects[0]);
			AddOpAction->NodeTemplate = OpNode;
		}
	}
}

void UEdGraphSchema_StateMachineData::GetSubNodeClasses(int32 SubNodeFlags, TArray<FGraphNodeClassData>& ClassData, UClass*& GraphNodeClass) const
{
	FStateMachineEditorModule& EditorModule = FModuleManager::GetModuleChecked<FStateMachineEditorModule>(TEXT("StateMachineEditorModule"));

	if (SubNodeFlags == EStateSubNode::Logic)
	{
		FGraphNodeClassHelper* ClassCache = EditorModule.GetLogicClassCache().Get();
		ClassCache->GatherClasses(ULogicDataBase::StaticClass(), ClassData);
		GraphNodeClass = UStateMachineGraphNode_Logic::StaticClass();
	}
	else
	{
		FGraphNodeClassHelper* ClassCache = EditorModule.GetActionClassCache().Get();
		ClassCache->GatherClasses(UActionDataBase::StaticClass(), ClassData);
		GraphNodeClass = UStateMachineGraphNode_Action::StaticClass();
	}
}
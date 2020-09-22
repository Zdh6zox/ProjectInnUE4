// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineGraphNode_Transition.h"
#include "SMTransitionSchema.h"
#include "SMTransitionGraph.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "StateMachineGraphNode_State.h"
#include "EdGraphUtilities.h"
#include "StateMachineEditorTypes.h"
#include "Data/State/StateData.h"
#include "Data/State/TransitionData.h"

UStateMachineGraphNode_Transition::UStateMachineGraphNode_Transition(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UStateMachineGraphNode_Transition::AllocateDefaultPins()
{
	UEdGraphPin* Inputs = CreatePin(EGPD_Input, UStateMachineEditorTypes::PinCategory_StateNode, TEXT("In"));
	Inputs->bHidden = true;
	UEdGraphPin* Outputs = CreatePin(EGPD_Output, UStateMachineEditorTypes::PinCategory_StateNode, TEXT("Out"));
	Outputs->bHidden = true;
}

FText UStateMachineGraphNode_Transition::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Transition");
}

void UStateMachineGraphNode_Transition::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{

}

void UStateMachineGraphNode_Transition::DestroyNode()
{
	UStateMachineGraphNode_State* preState = GetPreviousState();
	if (preState != nullptr)
	{
		UStateData* stateData = Cast<UStateData>(preState->NodeInstance);
		UTransitionData* transData = Cast<UTransitionData>(NodeInstance);
		stateData->Transitions.Remove(transData);
	}

	Super::DestroyNode();
}

void UStateMachineGraphNode_Transition::CreateBoundGraph()
{
	// Create a new animation graph
	check(BoundGraph == NULL);
	BoundGraph = FBlueprintEditorUtils::CreateNewGraph(this, NAME_None, USMTransitionGraph::StaticClass(), USMTransitionSchema::StaticClass());
	check(BoundGraph);

	// Initialize the anim graph
	const UEdGraphSchema* Schema = BoundGraph->GetSchema();
	Schema->CreateDefaultNodesForGraph(*BoundGraph);

	// Add the new graph as a child of our parent graph
	UEdGraph* ParentGraph = GetGraph();

	if (ParentGraph->SubGraphs.Find(BoundGraph) == INDEX_NONE)
	{
		ParentGraph->SubGraphs.Add(BoundGraph);
	}
}

void UStateMachineGraphNode_Transition::PostPlacedNewNode()
{
	//CreateBoundGraph();
}

UStateMachineGraphNode_State* UStateMachineGraphNode_Transition::GetPreviousState() const
{
	if (Pins[0]->LinkedTo.Num() > 0)
	{
		return Cast<UStateMachineGraphNode_State>(Pins[0]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return NULL;
	}
}

UStateMachineGraphNode_State* UStateMachineGraphNode_Transition::GetNextState() const
{
	if (Pins[1]->LinkedTo.Num() > 0)
	{
		return Cast<UStateMachineGraphNode_State>(Pins[1]->LinkedTo[0]->GetOwningNode());
	}
	else
	{
		return NULL;
	}
}

void UStateMachineGraphNode_Transition::CreateConnections(UStateMachineGraphNode_State* PreviousState, UStateMachineGraphNode_State* NextState)
{
	// Previous to this
	Pins[0]->Modify();
	Pins[0]->LinkedTo.Empty();

	PreviousState->GetOutputPin()->Modify();
	Pins[0]->MakeLinkTo(PreviousState->GetOutputPin());

	// This to next
	Pins[1]->Modify();
	Pins[1]->LinkedTo.Empty();

	NextState->GetInputPin()->Modify();
	Pins[1]->MakeLinkTo(NextState->GetInputPin());
}
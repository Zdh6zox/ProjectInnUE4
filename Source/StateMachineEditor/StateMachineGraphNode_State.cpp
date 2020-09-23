// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineGraphNode_State.h"
#include "Data/State/StateData.h"
#include "StateMachineEditorTypes.h"
#include "StateMachineGraphNode_Transition.h"
#include "StateMachineGraphNode_Action.h"
#include "StateMachineGraphNode_Logic.h"

UStateMachineGraphNode_State::UStateMachineGraphNode_State(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UStateMachineGraphNode_State::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UStateMachineEditorTypes::PinCategory_StateNode, TEXT("In"));
	CreatePin(EGPD_Output, UStateMachineEditorTypes::PinCategory_StateNode, TEXT("Out"));
}

FText UStateMachineGraphNode_State::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	const UStateData* myState = Cast<UStateData>(NodeInstance);
	if (myState != NULL)
	{
		if (myState->StateName == "")
		{
			return FText::FromString(ClassData.GetClassName());
		}
		return FText::FromString(myState->StateName);
	}

	return Super::GetNodeTitle(TitleType);
}

void UStateMachineGraphNode_State::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	AddContextMenuActionsEnterActions(Menu, "StateSubNode", Context);
	AddContextMenuActionsExitActions(Menu, "StateSubNode", Context);
	AddContextMenuActionsLogics(Menu, "StateSubNode", Context);
}

void UStateMachineGraphNode_State::GetTransitionList(TArray<UStateMachineGraphNode_Transition *>& OutTransitions)
{
	// Normal transitions
	for (int32 LinkIndex = 0; LinkIndex < Pins[1]->LinkedTo.Num(); ++LinkIndex)
	{
		UEdGraphNode* TargetNode = Pins[1]->LinkedTo[LinkIndex]->GetOwningNode();
		if (UStateMachineGraphNode_Transition* Transition = Cast<UStateMachineGraphNode_Transition>(TargetNode))
		{
			OutTransitions.Add(Transition);
		}
	}

	// Bidirectional transitions where we are the 'backwards' link
	for (int32 LinkIndex = 0; LinkIndex < Pins[0]->LinkedTo.Num(); ++LinkIndex)
	{
		UEdGraphNode* TargetNode = Pins[0]->LinkedTo[LinkIndex]->GetOwningNode();
		if (UStateMachineGraphNode_Transition* Transition = Cast<UStateMachineGraphNode_Transition>(TargetNode))
		{
			if (Transition->Bidirectional)
			{
				OutTransitions.Add(Transition);
			}
		}
	}
}

void UStateMachineGraphNode_State::OnSubNodeAdded(UAIGraphNode* SubNode)
{
	UStateMachineGraphNode* smGraphNode = Cast<UStateMachineGraphNode>(SubNode);

	if (UStateMachineGraphNode_Action* actionNode = Cast<UStateMachineGraphNode_Action>(SubNode))
	{
		if (actionNode->IsEnterAction)
		{
			EnterActions.Add(actionNode);
		}
		else
		{
			ExitActions.Add(actionNode);
		}
	}
	else if (UStateMachineGraphNode_Logic* logicNode = Cast<UStateMachineGraphNode_Logic>(SubNode))
	{
		Logics.Add(logicNode);
	}
}

void UStateMachineGraphNode_State::OnSubNodeRemoved(UAIGraphNode* SubNode)
{

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineGraphNode_Action.h"

UStateMachineGraphNode_Action::UStateMachineGraphNode_Action(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UStateMachineGraphNode_Action::AllocateDefaultPins()
{

}

FText UStateMachineGraphNode_Action::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Action");
}

void UStateMachineGraphNode_Action::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{

}
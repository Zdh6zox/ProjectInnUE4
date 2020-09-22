// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineGraphNode_Logic.h"

UStateMachineGraphNode_Logic::UStateMachineGraphNode_Logic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UStateMachineGraphNode_Logic::AllocateDefaultPins()
{

}

FText UStateMachineGraphNode_Logic::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString("Logic");
}

void UStateMachineGraphNode_Logic::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{

}
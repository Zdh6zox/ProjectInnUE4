// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineGraphNode_Action.h"
#include "Data/Action/ActionDataBase.h"

UStateMachineGraphNode_Action::UStateMachineGraphNode_Action(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UStateMachineGraphNode_Action::AllocateDefaultPins()
{

}

FText UStateMachineGraphNode_Action::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	const UActionDataBase* myAction = Cast<UActionDataBase>(NodeInstance);
	if (myAction != NULL)
	{
		if (myAction->ActionName == "")
		{
			return FText::FromString(ClassData.GetClassName());
		}
		return FText::FromString(myAction->ActionName);
	}

	return Super::GetNodeTitle(TitleType);
}

void UStateMachineGraphNode_Action::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineGraphNode_Logic.h"
#include "Data/Logic/LogicDataBase.h"

UStateMachineGraphNode_Logic::UStateMachineGraphNode_Logic(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UStateMachineGraphNode_Logic::AllocateDefaultPins()
{

}

FText UStateMachineGraphNode_Logic::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	const ULogicDataBase* myLogic = Cast<ULogicDataBase>(NodeInstance);
	if (myLogic != NULL)
	{
		if (myLogic->LogicName == "")
		{
			return FText::FromString(ClassData.GetClassName());
		}
		return FText::FromString(myLogic->LogicName);
	}

	return Super::GetNodeTitle(TitleType);
}

void UStateMachineGraphNode_Logic::GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{

}

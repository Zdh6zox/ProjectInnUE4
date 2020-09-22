// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachineGraphNode.h"
#include "StateMachineGraphNode_Logic.generated.h"

/**
 * 
 */
UCLASS()
class STATEMACHINEEDITORMODULE_API UStateMachineGraphNode_Logic : public UStateMachineGraphNode
{
	GENERATED_UCLASS_BODY()

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	/** Gets a list of actions that can be done to this particular node */
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	//virtual bool CanPlaceBreakpoints() const override { return true; }
	
};

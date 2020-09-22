// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "StateMachineGraphNode.h"
#include "StateMachineGraphNode_State.generated.h"

/**
 * 
 */
class UStateMachineGraphNode_Transition; 
UCLASS()
class STATEMACHINEEDITORMODULE_API UStateMachineGraphNode_State : public UStateMachineGraphNode
{
	GENERATED_UCLASS_BODY()
	
public:
	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	/** Gets a list of actions that can be done to this particular node */
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	virtual void OnSubNodeAdded(UAIGraphNode* SubNode) override;
	virtual void OnSubNodeRemoved(UAIGraphNode* SubNode) override;

	void GetTransitionList(TArray<UStateMachineGraphNode_Transition*>& OutTransitions);
	//virtual bool CanPlaceBreakpoints() const override { return true; }
};

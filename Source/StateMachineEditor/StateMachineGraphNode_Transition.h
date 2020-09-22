// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachineGraphNode.h"
#include "StateMachineGraphNode_Transition.generated.h"

/**
 * 
 */
class UStateMachineGraphNode_State;

UCLASS()
class STATEMACHINEEDITORMODULE_API UStateMachineGraphNode_Transition : public UStateMachineGraphNode
{
	GENERATED_UCLASS_BODY()

public:
	// The transition logic graph for this transition (returning a boolean)
	UPROPERTY()
	class UEdGraph* BoundGraph;

	/** This transition can go both directions */
	UPROPERTY(EditAnywhere, Category = Transition)
	bool Bidirectional;

	virtual void AllocateDefaultPins() override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	/** Gets a list of actions that can be done to this particular node */
	virtual void GetNodeContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const override;

	virtual void PostPlacedNewNode() override;

	virtual void DestroyNode() override;

	UStateMachineGraphNode_State* GetPreviousState() const;
	UStateMachineGraphNode_State* GetNextState() const;

	void CreateConnections(UStateMachineGraphNode_State* PreviousState, UStateMachineGraphNode_State* NextState);

private:
	void CreateBoundGraph();

};

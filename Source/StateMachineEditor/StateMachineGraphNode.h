// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGraphNode.h"
#include "StateMachineGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class STATEMACHINEEDITORMODULE_API UStateMachineGraphNode : public UAIGraphNode
{
	GENERATED_UCLASS_BODY()

	////~ Begin UEdGraphNode Interface
	//virtual class UBehaviorTreeGraph* GetBehaviorTreeGraph();
	//virtual void AllocateDefaultPins() override;
	//virtual FText GetTooltipText() const override;
	//virtual bool CanCreateUnderSpecifiedSchema(const UEdGraphSchema* DesiredSchema) const override;
	//virtual void FindDiffs(class UEdGraphNode* OtherNode, struct FDiffResults& Results) override;
	////~ End UEdGraphNode Interface
public:
	UPROPERTY()
	TArray<UStateMachineGraphNode*> EnterActions;

	UPROPERTY()
	TArray<UStateMachineGraphNode*> ExitActions;
	
	UPROPERTY()
	TArray<UStateMachineGraphNode*> Logics;

	UPROPERTY()
	TArray<UStateMachineGraphNode*> Transitions;

	//virtual int32 FindSubNodeDropIndex(UAIGraphNode* SubNode) const override;
	//virtual void InsertSubNodeAt(UAIGraphNode* SubNode, int32 DropIndex) override;

protected:
	/** creates add enter action... submenu */
	void CreateAddEnterActionSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const;

	/** creates add exit action... submenu */
	void CreateAddExitActionSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const;

	/** creates add logic... submenu */
	void CreateAddLogicSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const;

	/** add right click menu to create subnodes: EnterActions */
	void AddContextMenuActionsEnterActions(class UToolMenu* Menu, const FName SectionName, class UGraphNodeContextMenuContext* Context) const;

	/** add right click menu to create subnodes: ExitActions */
	void AddContextMenuActionsExitActions(class UToolMenu* Menu, const FName SectionName, class UGraphNodeContextMenuContext* Context) const;

	/** add right click menu to create subnodes: Logics */
	void AddContextMenuActionsLogics(class UToolMenu* Menu, const FName SectionName, class UGraphNodeContextMenuContext* Context) const;
};

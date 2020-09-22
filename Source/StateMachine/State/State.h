// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "State/Transition.h"

/**
 * 
 */
class FActionBase;
class FLogicBase;
class FActionExecutionContext;

class FState
{
public:
	FState();
	FState(FString name);
	~FState();

	void EnterState();
	void Update();
	void ExitState();

	void InitContext(UStateMachineComponent* owner);
	void ResetContext();

	const TArray<TSharedPtr<FTransition>>& GetTransitions() { return m_Transitions; }
	void AddTransition(TSharedPtr<FTransition> trans);
	void AddEnterAction(TSharedPtr<FActionBase> action);
	void AddExitAction(TSharedPtr<FActionBase> action);
	void AddUpdateLogic(TSharedPtr<FLogicBase> logic);
	FString GetStateName() { return m_StateName; }

private:
	TArray<TSharedPtr<FTransition>> m_Transitions;
	TArray<TSharedPtr<FActionBase>> m_EnterActions;
	TArray<TSharedPtr<FLogicBase>> m_UpdateLogics;
	TArray<TSharedPtr<FActionBase>> M_ExitActions;
	TSharedPtr<FActionExecutionContext> m_ExecutionContext;
	FString m_StateName;
};

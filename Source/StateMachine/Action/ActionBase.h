// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachineComponent.h"
/**
 * 
 */

enum class EActionExecuteState : uint8
{
    NotStarted,
	Running,
	Success,
	Failure
};

class STATEMACHINEMODULE_API FActionExecutionContext
{
public:
	UStateMachineComponent* ExecuterComponent;
};

class STATEMACHINEMODULE_API FActionBase
{
public:
	FActionBase(FString actionName);
	virtual ~FActionBase();

	virtual void Init(TWeakPtr<FActionExecutionContext> ctx);
	virtual void Execute(TWeakPtr<FActionExecutionContext> ctx);

protected:
	FString m_ActionName;
	EActionExecuteState m_ExecuteState = EActionExecuteState::NotStarted;
};

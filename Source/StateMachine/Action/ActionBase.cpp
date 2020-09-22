// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBase.h"
#include "StateMachineLog.h"

FActionBase::FActionBase(FString actionName)
{
	m_ActionName = actionName;
}

FActionBase::~FActionBase()
{
}

void FActionBase::Init(TWeakPtr<FActionExecutionContext> ctx)
{
	UE_LOG(LogStateMachine, Log, TEXT("Init Action : %s"), *m_ActionName);
	m_ExecuteState = EActionExecuteState::NotStarted;
}

void FActionBase::Execute(TWeakPtr<FActionExecutionContext> ctx)
{
	UE_LOG(LogStateMachine, Log, TEXT("Execute Action : %s"), *m_ActionName);

	if (m_ExecuteState == EActionExecuteState::NotStarted)
	{
		m_ExecuteState = EActionExecuteState::Running;
	}
}

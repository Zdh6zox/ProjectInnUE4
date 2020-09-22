// Fill out your copyright notice in the Description page of Project Settings.


#include "State.h"
#include "StateMachineLog.h"
#include "Logic/LogicBase.h"
#include "Action/ActionBase.h"

FState::FState()
{
	m_StateName = "Invalid";
}

FState::FState(FString name)
{
	m_StateName = name;
}

FState::~FState()
{
	//m_Transitions.Empty();

		//Reset States;
	//for (int i = 0; i < m_Transitions.Num(); ++i)
	//{
	//	m_Transitions[i].Reset();
	//}
}

void FState::EnterState()
{
	UE_LOG(LogStateMachine, Log, TEXT("Enter %s"), *m_StateName);

	for (int i = 0; i < m_EnterActions.Num(); ++i)
	{
		const TSharedPtr<FActionBase>& action = m_EnterActions[i];
		if (!action.IsValid())
		{
			UE_LOG(LogStateMachine, Error, TEXT("enter action %d is invalid"), i);
			continue;
		}

		action->Init(m_ExecutionContext);
		action->Execute(m_ExecutionContext);
	}

	for (int i = 0; i < m_UpdateLogics.Num(); ++i)
	{
		const TSharedPtr<FLogicBase>& logic = m_UpdateLogics[i];
		if (!logic.IsValid())
		{
			UE_LOG(LogStateMachine, Error, TEXT("logic %d is invalid"), i);
			continue;
		}

		logic->StartLogic(m_ExecutionContext);
	}
}

void FState::Update()
{
	//UE_LOG(LogTemp, Log, TEXT("Update %s"), *m_StateName);

	for (int i = 0;i< m_UpdateLogics.Num();++i)
	{
		const TSharedPtr<FLogicBase>& logic = m_UpdateLogics[i];
		if (!logic.IsValid())
		{
			UE_LOG(LogStateMachine, Error, TEXT("logic is null"));
			continue;
		}

		logic->UpdateLogic(m_ExecutionContext);
	}
}

void FState::ExitState()
{
	UE_LOG(LogStateMachine, Log, TEXT("Exit %s"), *m_StateName);

	for (int i = 0; i < M_ExitActions.Num(); ++i)
	{
		const TSharedPtr<FActionBase>& action = M_ExitActions[i];
		if (!action.IsValid())
		{
			UE_LOG(LogStateMachine, Error, TEXT("exit action %d is invalid"), i);
			continue;
		}

		action->Init(m_ExecutionContext);
		action->Execute(m_ExecutionContext);
	}
}

void FState::AddTransition(TSharedPtr<FTransition> trans)
{
	m_Transitions.Add(trans);
}

void FState::AddEnterAction(TSharedPtr<FActionBase> action)
{
	m_EnterActions.Add(action);
}

void FState::AddUpdateLogic(TSharedPtr<FLogicBase> logic)
{
	m_UpdateLogics.Add(logic);
}

void FState::AddExitAction(TSharedPtr<FActionBase> action)
{
	M_ExitActions.Add(action);
}

void FState::InitContext(UStateMachineComponent* owner)
{
	FActionExecutionContext* actionCtx = new FActionExecutionContext();

	actionCtx->ExecuterComponent = owner;

	m_ExecutionContext = MakeShareable(actionCtx);
}

void FState::ResetContext()
{
	m_ExecutionContext.Reset();
}
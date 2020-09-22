// Fill out your copyright notice in the Description page of Project Settings.


#include "IfElseLogic.h"
#include "StateMachineLog.h"
#include "Condition/ConditionBase.h"
#include "Action/ActionBase.h"

FIfElseLogic::FIfElseLogic()
{
}

FIfElseLogic::~FIfElseLogic()
{
}

void FIfElseLogic::StartLogic(TWeakPtr<FActionExecutionContext> ctx)
{
	UE_LOG(LogStateMachine, Log, TEXT("Start IfElse Logic"));

}

void FIfElseLogic::UpdateLogic(TWeakPtr<FActionExecutionContext> ctx)
{
	//UE_LOG(LogStateMachine, Log, TEXT("Update IfElse Logic"));

	if (!m_Condition.IsValid())
	{
		return;
	}

	if (!ctx.IsValid())
	{
		return;
	}

	FConditionBase* condition = m_Condition.Get();

	if (condition->GetIsVerified(ctx.Pin()->ExecuterComponent))
	{
		UE_LOG(LogStateMachine, Log, TEXT("Try To Execute Positive Action"));
		if (m_PositiveAction.IsValid())
		{
			FActionBase* positiveAction = m_PositiveAction.Get();
			positiveAction->Execute(ctx);
		}
	}
	else
	{
		UE_LOG(LogStateMachine, Log, TEXT("Try To Execute Negative Action"));
		if (m_NegativeAction.IsValid())
		{
			FActionBase* negativeAction = m_NegativeAction.Get();
			negativeAction->Execute(ctx);
		}
	}
}

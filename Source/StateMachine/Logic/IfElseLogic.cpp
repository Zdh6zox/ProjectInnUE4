// Fill out your copyright notice in the Description page of Project Settings.


#include "IfElseLogic.h"
#include "StateMachineLog.h"
#include "Condition/Expression.h"
#include "Condition/ConditionBase.h"
#include "Action/ActionBase.h"

FIfElseLogic::FIfElseLogic()
{
}

FIfElseLogic::~FIfElseLogic()
{
}

void FIfElseLogic::SetExpression(FExpression* expression)
{
	m_Expression = MakeShareable(expression);
}

void FIfElseLogic::SetPositiveAction(FActionBase* action)
{
	m_PositiveAction = MakeShareable(action);
}

void FIfElseLogic::SetNegativeAction(FActionBase* action)
{
	m_NegativeAction = MakeShareable(action);
}

void FIfElseLogic::StartLogic(TWeakPtr<FActionExecutionContext> ctx)
{
	UE_LOG(LogStateMachine, Log, TEXT("Start IfElse Logic"));

}

void FIfElseLogic::UpdateLogic(TWeakPtr<FActionExecutionContext> ctx)
{
	//UE_LOG(LogStateMachine, Log, TEXT("Update IfElse Logic"));

	if (!m_Expression.IsValid())
	{
		return;
	}

	if (!ctx.IsValid())
	{
		return;
	}

	if (m_Expression->GetExpressionResult(ctx.Pin()->ExecuterComponent))
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

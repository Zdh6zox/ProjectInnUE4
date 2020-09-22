// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/ConditionBase.h"

/**
 * 
 */

class UStateMachineComponent;

enum EExpressionOperatorType
{
	And,
	Or,
	Not,
	Leftbracket,
	Rightbracket
};

class FExpressionOperator
{
public:
	FExpressionOperator(EExpressionOperatorType type);
	~FExpressionOperator();

	EExpressionOperatorType GetOperatorType() { return m_OperatorType; }

private:
	EExpressionOperatorType m_OperatorType;
};

class FExpression
{
public:
	FExpression(FString expressionStr, TArray<TSharedPtr<FConditionBase>> conditions);
	~FExpression();

	void ConstructExpression();
	bool GetExpressionResult(UStateMachineComponent* expressionOwner);
	void ResetExpression(UStateMachineComponent* expressionOwner);

private:
	bool m_IsEmpty = false;
	FString m_ExpressionStr;
	TSharedPtr<FExpressionOperator> m_PendingOperator;
	TArray<TSharedPtr<FConditionBase>> m_Conditions;
	TArray<TSharedPtr<FConditionBase>> m_SortedCondtions;
	TArray<TSharedPtr<FExpressionOperator>> m_Operators;
};
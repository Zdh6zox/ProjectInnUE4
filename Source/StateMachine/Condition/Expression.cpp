// Fill out your copyright notice in the Description page of Project Settings.


#include "Expression.h"
#include "Condition/ConditionBase.h"
#include "GameFramework/Actor.h"
#include "StateMachineLog.h"
#include "StateMachineComponent.h"

FExpression::FExpression(FString expressionStr,TArray<TSharedPtr<FConditionBase>> conditions)
{
	m_ExpressionStr = expressionStr;
	m_Conditions = conditions;

	ConstructExpression();
}

FExpression::~FExpression()
{
}

bool FExpression::GetExpressionResult(UStateMachineComponent* expressionOwner)
{
	if (m_IsEmpty)
	{
		return true;
	}

	//Get all result of conditions;
	TArray<bool> resultArr;
	resultArr.Reserve(m_SortedCondtions.Num());

	for (int i =0;i<m_SortedCondtions.Num();++i)
	{
		resultArr.Push(m_SortedCondtions[i]->GetIsVerified(expressionOwner));
	}

	TArray<TSharedPtr<FExpressionOperator>> operatorsCopy = m_Operators;

	for (int i =0;i<operatorsCopy.Num();++i)
	{
		TSharedPtr<FExpressionOperator> curOperator = operatorsCopy[i];
		switch (curOperator->GetOperatorType())
		{
		case EExpressionOperatorType::And:
		{
			bool leftResult = resultArr.Pop();
			bool rightResult = resultArr.Pop();
			resultArr.Push(leftResult && rightResult);
		}
			break;
		case EExpressionOperatorType::Or:
		{
			bool leftResult = resultArr.Pop();
			bool rightResult = resultArr.Pop();
			resultArr.Push(leftResult || rightResult);
		}
			break;
		case EExpressionOperatorType::Not:
		{
			bool result = resultArr.Pop();
			resultArr.Push(!result);
		}
		    break;
		default:
			break;
		}
	}

	if (resultArr.Num() == 1)
	{
		return resultArr[0];
	}

	return false;
}

void FExpression::ConstructExpression()
{
	UE_LOG(LogStateMachineConstruct, Log, TEXT("Expression Str : %s"), *m_ExpressionStr);

	if (m_ExpressionStr == "")
	{
		m_IsEmpty = true;
		return;
	}

	TArray<FString> processedExpressionStrArr;

	m_ExpressionStr.ParseIntoArray(processedExpressionStrArr, TEXT("*"));

	for (int i = 0; i < processedExpressionStrArr.Num(); ++i)
	{
		FString processedExpressionStr = processedExpressionStrArr[i];

		UE_LOG(LogStateMachineConstruct, Log, TEXT("Splited Index : %d, result : %s"), i, *processedExpressionStr);

		bool isCondition = false;

		for (TSharedPtr<FConditionBase> condition : m_Conditions)
		{
			if (processedExpressionStr.Contains(condition->GetConditionName()))
			{
				m_SortedCondtions.Push(condition);
				isCondition = true;
				break;
			}
		}

		if (isCondition)
		{
			continue;
		}


		if (processedExpressionStr == "||")
		{
			FExpressionOperator* newOperator = new FExpressionOperator(EExpressionOperatorType::Or);
			m_Operators.Push(MakeShareable(newOperator));
		}
		else if (processedExpressionStr == "&&")
		{
			FExpressionOperator* newOperator = new FExpressionOperator(EExpressionOperatorType::And);
			m_Operators.Push(MakeShareable(newOperator));
		}
		else if (processedExpressionStr == "!")
		{
			FExpressionOperator* newOperator = new FExpressionOperator(EExpressionOperatorType::Not);
			m_Operators.Push(MakeShareable(newOperator));
		}
	}
}

void FExpression::ResetExpression(UStateMachineComponent* expressionOwner)
{
	for (int i = 0; i < m_SortedCondtions.Num(); ++i)
	{
		m_SortedCondtions[i]->ResetCondition(expressionOwner);
	}
}

FExpressionOperator::FExpressionOperator(EExpressionOperatorType type)
{
	m_OperatorType = type;
}

FExpressionOperator::~FExpressionOperator()
{
}
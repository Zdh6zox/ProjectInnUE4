// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpressionData.h"

FExpression* FExpressionData::CreateExpression()
{
	TArray<TSharedPtr<FConditionBase>> conditionArr;

	for (UConditionDataBase* conditionData : Conditions)
	{
		FConditionBase* condition = conditionData->ConstructCondition();
		if (condition != nullptr)
		{
			conditionArr.Add(MakeShareable(condition));
		}
	}

	FExpression* expression = new FExpression(ExpressionStr, conditionArr);

	return expression;
}
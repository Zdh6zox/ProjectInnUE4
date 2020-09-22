// Fill out your copyright notice in the Description page of Project Settings.


#include "TimedConditionData.h"
#include "Condition/TimedCondition.h"

FConditionBase* UTimedConditionData::ConstructCondition()
{
	if (ExpressionData.ExpressionStr == "")
	{
		FTimedCondition* newTimedCondition = new FTimedCondition(ConditionName, Duration);
		return newTimedCondition;
	}
	else
	{
		FTimedCondition* newTimedCondition = new FTimedCondition(ConditionName, Duration,ExpressionData.CreateExpression());
		return newTimedCondition;
	}
}
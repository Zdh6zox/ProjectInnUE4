// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstConditionData.h"
#include "Condition/ConstCondition.h"

FConditionBase* UConstConditionData::ConstructCondition()
{
	FConstCondition* constCondition = new FConstCondition(ConditionName, ConstValue);

	return constCondition;
}
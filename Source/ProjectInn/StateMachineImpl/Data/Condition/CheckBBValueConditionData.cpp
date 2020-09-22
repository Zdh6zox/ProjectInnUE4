// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckBBValueConditionData.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"

//TSharedPtr<FConditionBase> UCheckBBValueConditionData::ConstructCondition()
//{
//	if (UBlackboardKeyType_Bool* boolKey = Cast<UBlackboardKeyType_Bool>(KeyType))
//	{
//		FCheckBlackboardValueCondition_Bool* checkBBValueCondition_Bool = new FCheckBlackboardValueCondition_Bool(ConditionName, KeyToCheck, CheckType, CheckingBoolValue);
//
//		return MakeShareable(checkBBValueCondition_Bool);
//	}
//	else if (UBlackboardKeyType_Float* floatKey = Cast<UBlackboardKeyType_Float>(KeyType))
//	{
//		FCheckBlackboardValueCondition_Float* checkBBValueCondition_Float = new FCheckBlackboardValueCondition_Float(ConditionName, KeyToCheck, CheckType, CheckingFloatValue);
//
//		return MakeShareable(checkBBValueCondition_Float);
//	}
//	else if (UBlackboardKeyType_Int* intKey = Cast<UBlackboardKeyType_Int>(KeyType))
//	{
//		FCheckBlackboardValueCondition_Int* checkBBValueCondition_Int = new FCheckBlackboardValueCondition_Int(ConditionName, KeyToCheck, CheckType, CheckingIntValue);
//
//		return MakeShareable(checkBBValueCondition_Int);
//	}
//	else
//	{
//		return nullptr;
//	}
//}

FConditionBase* UCheckBBF32ValueConditionData::ConstructCondition()
{
	FCheckBlackboardValueCondition_Float* checkBBValueCondition_Float = new FCheckBlackboardValueCondition_Float(ConditionName, KeyToCheck, CheckType, CheckingFloatValue);

	return checkBBValueCondition_Float;
}

FConditionBase* UCheckBBIntValueConditionData::ConstructCondition()
{
	FCheckBlackboardValueCondition_Int* checkBBValueCondition_Int = new FCheckBlackboardValueCondition_Int(ConditionName, KeyToCheck, CheckType, CheckingIntValue);

	return checkBBValueCondition_Int;
}

FConditionBase* UCheckBBBoolValueConditionData::ConstructCondition()
{
	FCheckBlackboardValueCondition_Bool* checkBBValueCondition_Bool = new FCheckBlackboardValueCondition_Bool(ConditionName, KeyToCheck, CheckType, CheckingBoolValue);

	return checkBBValueCondition_Bool;
}
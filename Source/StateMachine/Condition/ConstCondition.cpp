// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstCondition.h"

FConstCondition::FConstCondition(FString conditionName, bool result)
	:FConditionBase(conditionName)
{
	m_Result = result;
}

FConstCondition::~FConstCondition()
{
}

void FConstCondition::UpdateCondition(UStateMachineComponent* conditionOwner)
{
	Super::UpdateCondition(conditionOwner);
	m_IsVerified = m_Result;
}

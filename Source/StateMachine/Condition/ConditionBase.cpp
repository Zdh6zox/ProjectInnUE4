// Fill out your copyright notice in the Description page of Project Settings.


#include "ConditionBase.h"
#include "StateMachineLog.h"
#include "GameFramework/Actor.h"
#include "StateMachineComponent.h"

FConditionBase::FConditionBase(FString conditionName)
{
	m_ConditionName = conditionName;
}

FConditionBase::~FConditionBase()
{
}

bool FConditionBase::GetIsVerified(UStateMachineComponent* conditionOwner)
{
	if (conditionOwner == nullptr)
	{
		UE_LOG(LogStateMachineCondition, Error, TEXT("Invalid Condition owner for %s"), *m_ConditionName);
		return false;
	}

	UpdateCondition(conditionOwner);

	return m_IsVerified;
}

void FConditionBase::UpdateCondition(UStateMachineComponent* conditionOwner)
{
	AActor* actorOwner = conditionOwner->GetOwner();
	//UE_LOG(LogStateMachineCondition, Log, TEXT("Update Condition %s on %s"), *m_ConditionName, *conditionOwner->Execute_GetDebugName(actorOwner));
}

void FConditionBase::ResetCondition(UStateMachineComponent* conditionOwner)
{
	AActor* actorOwner = conditionOwner->GetOwner();
	//UE_LOG(LogStateMachineCondition, Log, TEXT("Reset Condition %s on %s"), *m_ConditionName, *conditionOwner->Execute_GetDebugName(actorOwner));

	m_IsVerified = false;
}

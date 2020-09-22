// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class UStateMachineComponent;
/**
 * 
 */
class STATEMACHINEMODULE_API FConditionBase
{
public:
	FConditionBase(FString conditionName);
	virtual ~FConditionBase();

	bool GetIsVerified(UStateMachineComponent* conditionOwner);
	virtual void UpdateCondition(UStateMachineComponent* conditionOwner);

	virtual void ResetCondition(UStateMachineComponent* conditionOwner);

	FString GetConditionName() { return m_ConditionName; }
	void SetConditionName(FString name) { m_ConditionName = name; }

protected:
	FString m_ConditionName;
	bool m_IsVerified = false;
};

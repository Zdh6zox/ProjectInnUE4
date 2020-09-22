// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/ConditionBase.h"
/**
 * 
 */
class FConstCondition : public FConditionBase
{
public:
	typedef FConditionBase Super;
	FConstCondition(FString conditionName, bool result);
	~FConstCondition();

	virtual void UpdateCondition(UStateMachineComponent* conditionOwner);

private:
	bool m_Result;
};
 
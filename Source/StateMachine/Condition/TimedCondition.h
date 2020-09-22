// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/Expression.h"
#include "Condition/ConditionBase.h"

/**
 * 
 */
class STATEMACHINEMODULE_API FTimedCondition : public FConditionBase
{
public:
	typedef FConditionBase Super;

	FTimedCondition(FString conditionName, float duration, FExpression* expression);
	FTimedCondition(FString conditionName, float duration);

	virtual void UpdateCondition(UStateMachineComponent* conditionOwner) override;
	virtual void ResetCondition(UStateMachineComponent* conditionOwner) override;

private:
	TSharedPtr<FExpression> m_Expression;
	float m_Duration;
	float m_PassedTime;
};

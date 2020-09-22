// Fill out your copyright notice in the Description page of Project Settings.


#include "TimedCondition.h"
#include "GameFramework/Actor.h"
#include "StateMachineComponent.h"
#include "Engine/World.h"

FTimedCondition::FTimedCondition(FString conditionName, float duration, FExpression* expression)
	: FConditionBase(conditionName)
{
	m_Expression = MakeShareable(expression);
	m_PassedTime = 0.0f;
	m_Duration = duration;
}

FTimedCondition::FTimedCondition(FString conditionName, float duration)
	: FConditionBase(conditionName)
{
	FExpression* emptyExpression = new FExpression("", TArray<TSharedPtr<FConditionBase>>());
	m_Expression = MakeShareable(emptyExpression);
	m_PassedTime = 0.0f;
	m_Duration = duration;
}

void FTimedCondition::UpdateCondition(UStateMachineComponent* conditionOwner)
{
	Super::UpdateCondition(conditionOwner);

	AActor* actorOwner = Cast<AActor>(conditionOwner);

	if (m_PassedTime >= m_Duration)
	{
		m_IsVerified = true;
		return;
	}

	if (m_Expression->GetExpressionResult(conditionOwner))
	{
		float deltaTime = conditionOwner->GetWorld()->GetDeltaSeconds();
		m_PassedTime += deltaTime;
	}
	else
	{
		m_PassedTime = 0.0f;
	}
}

void FTimedCondition::ResetCondition(UStateMachineComponent* conditionOwner)
{
	Super::ResetCondition(conditionOwner);

	m_Expression->ResetExpression(conditionOwner);
	m_PassedTime = 0.0f;
}

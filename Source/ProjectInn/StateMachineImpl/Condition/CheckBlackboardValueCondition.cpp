// Fill out your copyright notice in the Description page of Project Settings.


#include "CheckBlackboardValueCondition.h"
#include "StateMachineLog.h"
#include "Character/Customer/Customer.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "StateMachineComponent.h"

FCheckBlackboardValueCondition::FCheckBlackboardValueCondition(FString conditionName, FName blackboardKey, ECheckOperationType checkType)
	: FConditionBase(conditionName)
{
	m_CheckingBlackboardKey = blackboardKey;
	m_CheckType = checkType;
}

FCheckBlackboardValueCondition::~FCheckBlackboardValueCondition()
{
}

void FCheckBlackboardValueCondition::UpdateCondition(UStateMachineComponent* conditionOwner)
{
	Super::UpdateCondition(conditionOwner);

	ACustomer* customer = Cast<ACustomer>(conditionOwner->GetOwner());
	if (customer == nullptr)
	{
		UE_LOG(LogStateMachineCondition, Error, TEXT("Invalid Condition Owner"));
		m_IsVerified = false;
		return;
	}
	UBlackboardComponent* bbComp = customer->FindComponentByClass<UBlackboardComponent>();
	if (bbComp == nullptr)
	{
		UE_LOG(LogStateMachineCondition, Error, TEXT("Condition Owner %s doesn't have BlackboardComponent"),*customer->GetName());
		return;
	}

	m_IsVerified = IsCheckOperationMet(bbComp);

	//
}

void FCheckBlackboardValueCondition::ResetCondition(UStateMachineComponent* conditionOwner)
{
	Super::ResetCondition(conditionOwner);
}

FCheckBlackboardValueCondition_Float::FCheckBlackboardValueCondition_Float(FString conditionName, FName blackboardKey, ECheckOperationType checkType, float checkingValue)
	:Super(conditionName, blackboardKey, checkType)
{
	m_CheckingValue = checkingValue;
}

FCheckBlackboardValueCondition_Bool::FCheckBlackboardValueCondition_Bool(FString conditionName, FName blackboardKey, ECheckOperationType checkType, bool checkingValue)
	: Super(conditionName, blackboardKey, checkType)
{
	m_CheckingValue = checkingValue;
}

FCheckBlackboardValueCondition_Int::FCheckBlackboardValueCondition_Int(FString conditionName, FName blackboardKey, ECheckOperationType checkType, int checkingValue)
	: Super(conditionName, blackboardKey, checkType)
{
	m_CheckingValue = checkingValue;
}

bool FCheckBlackboardValueCondition_Float::IsCheckOperationMet(UBlackboardComponent* bbComp)
{
	if (bbComp != nullptr)
	{
		switch (m_CheckType)
		{
		case ECheckOperationType::GreaterOrEqual:
			return m_CheckingValue >= bbComp->GetValueAsFloat(m_CheckingBlackboardKey);
		case ECheckOperationType::Equal:
			return m_CheckingValue == bbComp->GetValueAsFloat(m_CheckingBlackboardKey);
		case ECheckOperationType::GreaterThan:
			return m_CheckingValue > bbComp->GetValueAsFloat(m_CheckingBlackboardKey);
		case ECheckOperationType::LessOrEqual:
			return m_CheckingValue <= bbComp->GetValueAsFloat(m_CheckingBlackboardKey);
		case ECheckOperationType::LessThan:
			return m_CheckingValue < bbComp->GetValueAsFloat(m_CheckingBlackboardKey);
		case ECheckOperationType::NotEqual:
			return m_CheckingValue != bbComp->GetValueAsFloat(m_CheckingBlackboardKey);
		default:
			break;
		}
	}

	return false;
}

bool FCheckBlackboardValueCondition_Bool::IsCheckOperationMet(UBlackboardComponent* bbComp)
{
	if (bbComp != nullptr)
	{
		switch (m_CheckType)
		{
		case ECheckOperationType::Equal:
			return m_CheckingValue == bbComp->GetValueAsBool(m_CheckingBlackboardKey);
		case ECheckOperationType::NotEqual:
			return m_CheckingValue != bbComp->GetValueAsBool(m_CheckingBlackboardKey);
		default:
			break;
		}
	}

	return false;
}

bool FCheckBlackboardValueCondition_Int::IsCheckOperationMet(UBlackboardComponent* bbComp)
{
	if (bbComp != nullptr)
	{
		switch (m_CheckType)
		{
		case ECheckOperationType::GreaterOrEqual:
			return m_CheckingValue >= bbComp->GetValueAsInt(m_CheckingBlackboardKey);
		case ECheckOperationType::Equal:
			return m_CheckingValue == bbComp->GetValueAsInt(m_CheckingBlackboardKey);
		case ECheckOperationType::GreaterThan:
			return m_CheckingValue > bbComp->GetValueAsInt(m_CheckingBlackboardKey);
		case ECheckOperationType::LessOrEqual:
			return m_CheckingValue <= bbComp->GetValueAsInt(m_CheckingBlackboardKey);
		case ECheckOperationType::LessThan:
			return m_CheckingValue < bbComp->GetValueAsInt(m_CheckingBlackboardKey);
		case ECheckOperationType::NotEqual:
			return m_CheckingValue != bbComp->GetValueAsInt(m_CheckingBlackboardKey);
		default:
			break;
		}
	}

	return false;
}


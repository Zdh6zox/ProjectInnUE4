// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Condition/ConditionBase.h"
#include "CheckBlackboardValueCondition.generated.h"

UENUM(BlueprintType)
enum class ECheckOperationType : uint8
{
	GreaterThan,
	GreaterOrEqual,
	LessThan,
	LessOrEqual,
	Equal,
	NotEqual
};

/**
 * 
 */
class UBlackboardComponent;
class PROJECTINN_API FCheckBlackboardValueCondition : public FConditionBase
{
public:
	typedef FConditionBase Super;
	FCheckBlackboardValueCondition(FString conditionName, FName blackboardKey, ECheckOperationType checkType);
	~FCheckBlackboardValueCondition();

	virtual void UpdateCondition(UStateMachineComponent* conditionOwner) override;
	virtual void ResetCondition(UStateMachineComponent* conditionOwner) override;

	virtual bool IsCheckOperationMet(UBlackboardComponent* bbComp) { return false; }

protected:
	FName m_CheckingBlackboardKey;
	ECheckOperationType m_CheckType;
};

class PROJECTINN_API FCheckBlackboardValueCondition_Float : public FCheckBlackboardValueCondition
{
public:
	typedef FCheckBlackboardValueCondition Super;
	FCheckBlackboardValueCondition_Float(FString conditionName, FName blackboardKey, ECheckOperationType checkType, float checkingValue);

	virtual bool IsCheckOperationMet(UBlackboardComponent* bbComp) override;

private:
	float m_CheckingValue;
};

class PROJECTINN_API FCheckBlackboardValueCondition_Int : public FCheckBlackboardValueCondition
{
public:
	typedef FCheckBlackboardValueCondition Super;
	FCheckBlackboardValueCondition_Int(FString conditionName, FName blackboardKey, ECheckOperationType checkType, int checkingValue);

	virtual bool IsCheckOperationMet(UBlackboardComponent* bbComp) override;
private:
	int m_CheckingValue;
};

class PROJECTINN_API FCheckBlackboardValueCondition_Bool : public FCheckBlackboardValueCondition
{
public:
	typedef FCheckBlackboardValueCondition Super;
	FCheckBlackboardValueCondition_Bool(FString conditionName, FName blackboardKey, ECheckOperationType checkType, bool checkingValue);

	virtual bool IsCheckOperationMet(UBlackboardComponent* bbComp) override;
private:
	bool m_CheckingValue;
};

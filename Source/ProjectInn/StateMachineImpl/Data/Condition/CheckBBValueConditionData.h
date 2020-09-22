// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/Condition/ConditionDataBase.h"
#include "StateMachineImpl/Condition/CheckBlackboardValueCondition.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "CheckBBValueConditionData.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class PROJECTINN_API UCheckBBValueConditionData : public UConditionDataBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		FName KeyToCheck;
};

UCLASS()
class PROJECTINN_API UCheckBBF32ValueConditionData : public UCheckBBValueConditionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		ECheckOperationType CheckType;

	UPROPERTY(EditAnywhere)
		float CheckingFloatValue;

	virtual FConditionBase* ConstructCondition() override;
};

UCLASS()
class PROJECTINN_API UCheckBBBoolValueConditionData : public UCheckBBValueConditionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		ECheckOperationType CheckType;

	UPROPERTY(EditAnywhere)
		bool CheckingBoolValue;

	virtual FConditionBase* ConstructCondition() override;
};

UCLASS()
class PROJECTINN_API UCheckBBIntValueConditionData : public UCheckBBValueConditionData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		ECheckOperationType CheckType;

	UPROPERTY(EditAnywhere)
		int CheckingIntValue;

	virtual FConditionBase* ConstructCondition() override;
};

UCLASS()
class PROJECTINN_API UCheckBBStringValueConditionData : public UCheckBBValueConditionData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		FString CheckingStringValue;
};

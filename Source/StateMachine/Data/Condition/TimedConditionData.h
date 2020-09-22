// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Condition/ConditionDataBase.h"
#include "Data/Condition/ExpressionData.h"
#include "TimedConditionData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STATEMACHINEMODULE_API UTimedConditionData : public UConditionDataBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FExpressionData ExpressionData;

	virtual FConditionBase* ConstructCondition() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateMachine/Data/Condition/ConditionDataBase.h"
#include "IsReachDestinationData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class PROJECTINN_API UIsReachDestinationData : public UConditionDataBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName DestinationKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Threshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Test_Result;

	virtual FConditionBase* ConstructCondition() override;
};

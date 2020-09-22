// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Condition/ConditionDataBase.h"
#include "ConstConditionData.generated.h"

/**
 * 
 */
UCLASS()
class STATEMACHINEMODULE_API UConstConditionData : public UConditionDataBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		bool ConstValue;

	virtual FConditionBase* ConstructCondition() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Logic/LogicDataBase.h"
#include "Data/Condition/ConditionDataBase.h"
#include "Data/Action/ActionDataBase.h"
#include "StepLogicData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STATEMACHINEMODULE_API UStepLogicData : public ULogicDataBase
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Instanced)
		TArray<UConditionDataBase*> Condition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Instanced)
		TArray <UActionDataBase*> Action;

	virtual FLogicBase* ConstructLogic() override;
};

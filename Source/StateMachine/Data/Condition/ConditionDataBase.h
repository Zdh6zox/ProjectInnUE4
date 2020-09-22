// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Condition/ConditionBase.h"
#include "ConditionDataBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, DefaultToInstanced, Abstract, EditInlineNew)
class STATEMACHINEMODULE_API UConditionDataBase : public UObject
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString ConditionName;

	virtual FConditionBase* ConstructCondition() { return nullptr; }
};

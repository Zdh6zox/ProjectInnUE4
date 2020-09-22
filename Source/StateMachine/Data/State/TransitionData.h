// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Condition/ExpressionData.h"
#include "TransitionData.generated.h"

/**
 * 
 */
class UStateData;
class FTransition;

UCLASS(BlueprintType, EditInlineNew, DefaultToInstanced)
class STATEMACHINEMODULE_API UTransitionData : public UObject
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString NextStateName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FExpressionData Expression;

	FTransition* CreateTransition();
};

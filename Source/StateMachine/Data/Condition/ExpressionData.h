// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Condition/Expression.h"
#include "ConditionDataBase.h"
#include "GameFramework/Actor.h"
#include "ExpressionData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct STATEMACHINEMODULE_API FExpressionData
{
	GENERATED_USTRUCT_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TArray<UConditionDataBase*> Conditions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString ExpressionEquation;

	UPROPERTY(EditAnywhere)
		FString ExpressionStr;

	FExpression* CreateExpression();
};

UCLASS()
class STATEMACHINEMODULE_API UExpressionStringConstructor : public UObject
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UConditionDataBase*> Conditions;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FString ExpressionEquation;

	UPROPERTY()
		FString ExpressionStr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FExpressionData ConstructingExpression;
};

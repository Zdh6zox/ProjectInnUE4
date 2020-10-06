// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SharedEnumTypes.h"
#include "Ingredient.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTINN_API FIngredient
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		FName IngredientName;

	UPROPERTY(EditAnywhere)
		EIngredientType IngredientType;
};

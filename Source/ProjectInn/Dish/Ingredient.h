// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ingredient.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EIngredientType : uint8
{
	Meat UMETA(DisplayName = "肉类"),
	Vegetable UMETA(DisplayName = "蔬菜类"),
	Oil UMETA(DisplayName = "油类"),
	Seasoning  UMETA(DisplayName = "调料")
};

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

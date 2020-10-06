// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "Dish/Flavour.h"
#include "Dish/Ingredient.h"
#include "SharedEnumTypes.h"
#include "Recipe.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTINN_API FRecipe : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		FName RecipeName;

	UPROPERTY(EditAnywhere)
		ERecipeRegionType RegionType;

	UPROPERTY(EditAnywhere)
		ERecipeCategoryType CategoryType;

	UPROPERTY(EditAnywhere)
		TArray<FFlavour> Flavours;

	UPROPERTY(EditAnywhere)
		TArray<FIngredient> Ingredients;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "Dish/Flavour.h"
#include "Dish/Ingredient.h"
#include "Recipe.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class ERecipeRegionType : uint8
{
	Chuan UMETA(DisplayName = "川菜"), //川菜
	Lu UMETA(DisplayName = "鲁菜"), //鲁菜
	Yue UMETA(DisplayName = "粤菜"), //粤菜
	Su UMETA(DisplayName = "苏菜"), //苏菜
	Zhe UMETA(DisplayName = "浙菜"), //浙菜
	Min UMETA(DisplayName = "闽菜"), //闽菜
	Xiang UMETA(DisplayName = "湘菜"), //湘菜
	Hui UMETA(DisplayName = "徽菜")//徽菜
};

UENUM(BlueprintType)
enum class ERecipeCategoryType : uint8
{
	Soup UMETA(DisplayName = "汤"),
	Appetizer UMETA(DisplayName = "前菜"),
	MainDish UMETA(DisplayName = "主菜"),
	AssitantDish UMETA(DisplayName = "配菜"),
	Dessert UMETA(DisplayName = "甜点"),
	StapleFood UMETA(DisplayName = "主食")
};

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

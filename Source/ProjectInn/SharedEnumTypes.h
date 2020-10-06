// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EFloorBlockMaterial : uint8
{
	Mud UMETA(DisplayName = "泥地"),
	Plank UMETA(DisplayName = "木地板"),
	Granite UMETA(DisplayName = "青石板"),
	Bamboo UMETA(DisplayName = "竹地板"),
	Brick UMETA(DisplayName = "石砖"),
	GoldenBrick UMETA(DisplayName = "金砖"),
	Jade UMETA(DisplayName = "玉石")
};

UENUM(BlueprintType)
enum class ERelationType : uint8
{
	DirectRelative,
	Relative,
	Couple,
	Friend,
	Normal,
	Unlike,
	Enemy
};

UENUM(BlueprintType)
enum class EFlavourType : uint8
{
	Salty UMETA(DisplayName = "咸"),
	Brothy UMETA(DisplayName = "鲜"),
	Sweety UMETA(DisplayName = "甜"),
	Sour UMETA(DisplayName = "酸"),
	Bitter UMETA(DisplayName = "苦"),
	Spicy UMETA(DisplayName = "辣"),
	TongueNumbing UMETA(DisplayName = "麻"),
	Crisp UMETA(DisplayName = "脆"),
	Loose UMETA(DisplayName = "酥"),
	Juicy UMETA(DisplayName = "多汁"),
	Greasy UMETA(DisplayName = "油腻"),
	Tough UMETA(DisplayName = "硬"),
	Soft UMETA(DisplayName = "软")
};

UENUM(BlueprintType)
enum class EIngredientType : uint8
{
	Meat UMETA(DisplayName = "肉类"),
	Vegetable UMETA(DisplayName = "蔬菜类"),
	Oil UMETA(DisplayName = "油类"),
	Seasoning  UMETA(DisplayName = "调料")
};

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

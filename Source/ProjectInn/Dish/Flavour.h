// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Flavour.generated.h"

/**
 * 
 */
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

USTRUCT(BlueprintType)
struct PROJECTINN_API FFlavour
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		EFlavourType FlavourType;

	UPROPERTY(EditAnywhere)
		float FlavourDegree;
};

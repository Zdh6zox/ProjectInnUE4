// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SharedEnumTypes.h"
#include "Flavour.generated.h"

/**
 * 
 */
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

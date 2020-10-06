// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConstructableObjectData.h"
#include "BaseBlockData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTINN_API FBaseBlockData
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FConstructableObjectData> ConstructableDataList;
};

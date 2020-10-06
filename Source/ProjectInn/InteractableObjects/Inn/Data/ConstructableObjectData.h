// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "UObject/NoExportTypes.h"
#include "SharedEnumTypes.h"
#include "ConstructableObjectData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTINN_API FConstructableObjectData
{
	GENERATED_USTRUCT_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		EConstructableObjectType Type;

	UPROPERTY(EditAnywhere)
		int Level;

	UPROPERTY(EditAnywhere)
		int SizeX;

	UPROPERTY(EditAnywhere)
		int SizeY;

	UPROPERTY(EditAnywhere)
		TArray<int> OccupiedBlockIndices;

	UPROPERTY(EditAnywhere)
		float DamageDegree;
};

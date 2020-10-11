// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "BaseBlockData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTINN_API FBlockCoordinate
{
	GENERATED_USTRUCT_BODY();

	UPROPERTY(EditAnywhere)
		uint32 X = 0;

	UPROPERTY(EditAnywhere)
		uint32 Y = 0;

	FORCEINLINE friend bool operator==(const FBlockCoordinate& lhs, const FBlockCoordinate& rhs)
	{
		return (lhs.X == rhs.X) && (lhs.Y == rhs.Y);
	}

	FORCEINLINE friend uint32 GetTypeHash(const FBlockCoordinate& key)
	{
		uint32 hash = 0;
		hash = HashCombine(hash, GetTypeHash(key.X));
		hash = HashCombine(hash, GetTypeHash(key.Y));

		return hash;
	}
};

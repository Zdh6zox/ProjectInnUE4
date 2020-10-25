// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "UObject/NoExportTypes.h"
#include "BaseBlockData.h"
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
		int Layer;

	UPROPERTY(EditAnywhere)
		int SizeX;

	UPROPERTY(EditAnywhere)
		int SizeY;

	UPROPERTY(EditAnywhere)
		EDirectionType Direction;

	UPROPERTY(EditAnywhere)
		FBlockCoordinate OriginLocation;

	UPROPERTY(EditAnywhere)
		float DamageDegree;

	FORCEINLINE friend bool operator==(const FConstructableObjectData& lhs, const FConstructableObjectData& rhs)
	{
		return (lhs.Type == rhs.Type) && (lhs.Level == rhs.Level)
			&& (lhs.Layer == rhs.Layer) && (lhs.SizeX == rhs.SizeX) && (lhs.SizeY == rhs.SizeY)
			&& (lhs.OriginLocation.X == rhs.OriginLocation.X) && (lhs.OriginLocation.Y == rhs.OriginLocation.Y)
			&& (lhs.DamageDegree == rhs.DamageDegree);
	}
};

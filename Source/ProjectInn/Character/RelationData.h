// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RelationData.generated.h"

/**
 * 
 */
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

USTRUCT(BlueprintType)
struct PROJECTINN_API FRelationData
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere)
		ERelationType RelationType;

	UPROPERTY(EditAnywhere)
		float RelationScore;

	UPROPERTY(EditAnywhere)
		FName WithWho;
};

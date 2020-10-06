// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SharedEnumTypes.h"
#include "RelationData.generated.h"

/**
 * 
 */
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

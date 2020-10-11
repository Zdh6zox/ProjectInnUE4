// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h" 
#include "SharedEnumTypes.h"
#include "InnConstructableObjectAssetData.generated.h"

/**
 * 
 */
class AConstructableObject;
USTRUCT(BlueprintType)
struct PROJECTINN_API FInnConstructableObjectAssetData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		EConstructableObjectType ObjectType;

	UPROPERTY(EditAnywhere)
		int Level;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AConstructableObject> TemplateClass;
};

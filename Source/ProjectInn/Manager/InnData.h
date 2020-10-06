// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "InteractableObjects/Inn/TableData.h"
#include "InteractableObjects/Inn/Data/BaseBlockData.h"
#include "InnData.generated.h"
/**
 * 
 */

UCLASS(BlueprintType)
class PROJECTINN_API UInnData : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		int InnLevel;

	UPROPERTY(EditAnywhere)
		TArray<FTableData> Tables;

	UPROPERTY(EditAnywhere)
		TArray<FConstructableObjectData> ConstructableObjectsData;
};

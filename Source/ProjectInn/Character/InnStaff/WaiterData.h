// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterData.h"
#include "WaiterData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct PROJECTINN_API FWaiterData : public FCharacterData
{
	GENERATED_USTRUCT_BODY()
};

class PROJECTINN_API FWaiterDataRuntime
{
private:
	TSharedPtr<FCustomerData> DataBase;
};
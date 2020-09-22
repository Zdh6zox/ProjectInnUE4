// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RelationData.h"
#include "Engine/DataTable.h" 
#include "CharacterData.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECharacterClassType : uint8
{
	Beggar UMETA(DisplayName = "乞丐"), 
	Peasant UMETA(DisplayName = "农民"),
	Citizen UMETA(DisplayName = "市民"), 
	Councillor UMETA(DisplayName = "员外"), 
	Swordman UMETA(DisplayName = "侠客"), 
	Escort UMETA(DisplayName = "镖师"), 
	Merchant UMETA(DisplayName = "商人"), 
	Hooligan UMETA(DisplayName = "流氓"),
	Mafia UMETA(DisplayName = "地头蛇"),
	Waiter UMETA(DisplayName = "跑堂"),
	Cook UMETA(DisplayName = "厨师")
};

USTRUCT(BlueprintType)
struct PROJECTINN_API FCharacterData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		FName CharacterName;

	UPROPERTY(EditAnywhere)
		TArray<FRelationData> Relations;

	UPROPERTY(EditAnywhere)
		FText Description;

	UPROPERTY(EditAnywhere)
		ECharacterClassType CharacterClass;
};

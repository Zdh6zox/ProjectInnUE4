// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Logic/LogicBase.h"
#include "LogicDataBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, DefaultToInstanced, Abstract, EditInlineNew)
class STATEMACHINEMODULE_API ULogicDataBase : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Basic", DisplayName = "Logic Name")
		FString LogicName;

	virtual	FLogicBase* ConstructLogic() { return nullptr; }
};

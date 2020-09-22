// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Action/ActionBase.h"
#include "ActionDataBase.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, DefaultToInstanced, Abstract, EditInlineNew)
class STATEMACHINEMODULE_API UActionDataBase : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, DisplayName = "Action Name")
		FString ActionName;

	virtual FActionBase* CreateAction() { return nullptr; }

	
};

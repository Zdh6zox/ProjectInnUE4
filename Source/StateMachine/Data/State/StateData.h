// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateData.generated.h"

/**
 * 
 */
class FState;
class ULogicDataBase;
class UActionDataBase;
class UTransitionData;

UCLASS(BlueprintType,DefaultToInstanced, EditInlineNew)
class STATEMACHINEMODULE_API UStateData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString StateName = "NewState";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TArray<UActionDataBase*> EnterActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TArray<ULogicDataBase*> UpdateLogics;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TArray<UActionDataBase*> ExitActions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TArray<UTransitionData*> Transitions;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector2D StateLocation;
#endif

	UFUNCTION(BlueprintCallable)
		void RemoveLogicAtIndex(int index);

	FState* CreateState();
};

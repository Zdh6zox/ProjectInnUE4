// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StateMachineData.generated.h"

/**
 * 
 */
class UStateData;
class FState;
UCLASS(BlueprintType)
class STATEMACHINEMODULE_API UStateMachineData : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		TArray<UStateData*> States;

#if WITH_EDITORONLY_DATA
	/** Graph for State Machine */
	UPROPERTY()
		class UEdGraph*	SMGraph;

	/** Info about the graphs we last edited */
	UPROPERTY()
		TArray<FEditedDocumentInfo> LastEditedDocuments;
#endif

	TArray<TSharedPtr<FState>> CreateStatesWithTransition();
private:
	TSharedPtr<FState> FindStateViaName(const TArray<TSharedPtr<FState>> states, FString stateName);
};

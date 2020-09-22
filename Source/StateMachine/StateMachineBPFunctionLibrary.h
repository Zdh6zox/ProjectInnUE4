// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/Action/ActionDataBase.h"
#include "Data/Condition/ConditionDataBase.h"
#include "Data/Logic/LogicDataBase.h"
#include "StateMachineBPFunctionLibrary.generated.h"

/**
 * 
 */

UCLASS()
class STATEMACHINEMODULE_API UStateMachineBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()	
public:
	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	    static TArray<TSubclassOf<UActionDataBase>> GetActionClasses();

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	    static TArray<TSubclassOf<UConditionDataBase>> GetConditionClasses();

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	    static TArray<TSubclassOf<ULogicDataBase>> GetLogicClasses();

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
	    static ULogicDataBase* CreateLogic(UObject* outer, TSubclassOf<ULogicDataBase> logicClass);

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
		static void MarkStateMachineDataDirty(UObject* smAsset);

	UFUNCTION(BlueprintCallable, Category = "StateMachine")
		static TMap<FString, UProperty*> GetPropertyMap(UObject* smData);

};
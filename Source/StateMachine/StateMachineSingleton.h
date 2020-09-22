// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/Action/ActionDataBase.h"
#include "Data/Condition/ConditionDataBase.h"
#include "Data/Logic/LogicDataBase.h"
#include "StateMachineSingleton.generated.h"

/**
 * 
 */
UCLASS()
class STATEMACHINEMODULE_API UStateMachineSingleton : public UObject
{
	GENERATED_BODY()
	
public:
	UStateMachineSingleton() {}
	static UStateMachineSingleton* Get();
	void RegisterActionClass(TSubclassOf<UActionDataBase> actionClass);
	void RegisterConditionClass(TSubclassOf<UConditionDataBase> conditionClass);
	void RegisterLogicClass(TSubclassOf<ULogicDataBase> logicClass);
	TArray<TSubclassOf<UActionDataBase>> GetActionClasses() { return m_ActionClasses; }
	TArray<TSubclassOf<UConditionDataBase>> GetConditionClasses() { return m_ConditionClasses; }
	TArray<TSubclassOf<ULogicDataBase>> GetLogicClasses() { return m_LogicClasses; }

private:
	TArray<TSubclassOf<UActionDataBase>> m_ActionClasses;
	TArray<TSubclassOf<UConditionDataBase>> m_ConditionClasses;
	TArray<TSubclassOf<ULogicDataBase>> m_LogicClasses;
};

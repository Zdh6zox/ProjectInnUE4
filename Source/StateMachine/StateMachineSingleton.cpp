// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineSingleton.h"
#include "Engine/Engine.h"

void UStateMachineSingleton::RegisterActionClass(TSubclassOf<UActionDataBase> actionClass)
{
	m_ActionClasses.AddUnique(actionClass);
}

void UStateMachineSingleton::RegisterConditionClass(TSubclassOf<UConditionDataBase> conditionClass)
{
	m_ConditionClasses.AddUnique(conditionClass);
}

void UStateMachineSingleton::RegisterLogicClass(TSubclassOf<ULogicDataBase> logicClass)
{
	m_LogicClasses.AddUnique(logicClass);
}

UStateMachineSingleton* UStateMachineSingleton::Get()
{
#if WITH_EDITOR
	if (GEngine != nullptr)
	{
		return Cast<UStateMachineSingleton>(GEngine->GameSingleton);
	}
	return nullptr;
#else
	static UStateMachineSingleton* singletonObject = Cast<UStateMachineSingleton>(GEngine->GameSingleton);
	return singletonObject;
#endif
}
// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineBPFunctionLibrary.h"
#include "StateMachineSingleton.h"
#include "ProjectInn/ProjectInn.h"
#include "StateMachineModule.h"
#include "Modules/ModuleManager.h"

TArray<TSubclassOf<UActionDataBase>> UStateMachineBPFunctionLibrary::GetActionClasses()
{
	TArray<TSubclassOf<UActionDataBase>> actionClasses;

	FProjectInnModule& innModule = FModuleManager::LoadModuleChecked<FProjectInnModule>("ProjectInn");
    actionClasses.Append(innModule.GetActionClasses());

	FStateMachineModule& smModule = FModuleManager::LoadModuleChecked<FStateMachineModule>("StateMachineModule");
	actionClasses.Append(smModule.GetActionClasses());

	return actionClasses;
}

TArray<TSubclassOf<ULogicDataBase>> UStateMachineBPFunctionLibrary::GetLogicClasses()
{
	TArray<TSubclassOf<ULogicDataBase>> logicClasses;

	FProjectInnModule& innModule = FModuleManager::LoadModuleChecked<FProjectInnModule>("ProjectInn");
	logicClasses.Append(innModule.GetLogicClasses());

	FStateMachineModule& smModule = FModuleManager::LoadModuleChecked<FStateMachineModule>("StateMachineModule");
	logicClasses.Append(smModule.GetLogicClasses());
	return logicClasses;
}

TArray<TSubclassOf<UConditionDataBase>> UStateMachineBPFunctionLibrary::GetConditionClasses()
{
	TArray<TSubclassOf<UConditionDataBase>> conditionClasses;

	FProjectInnModule& innModule = FModuleManager::LoadModuleChecked<FProjectInnModule>("ProjectInn");
	conditionClasses.Append(innModule.GetConditionClasses());

	FStateMachineModule& smModule = FModuleManager::LoadModuleChecked<FStateMachineModule>("StateMachineModule");
	conditionClasses.Append(smModule.GetConditionClasses());
	return conditionClasses;
}

ULogicDataBase* UStateMachineBPFunctionLibrary::CreateLogic(UObject* outer, TSubclassOf<ULogicDataBase> logicClass)
{
	ULogicDataBase* logic = NewObject<ULogicDataBase>(outer, logicClass, NAME_None);

	return logic;
}

void UStateMachineBPFunctionLibrary::MarkStateMachineDataDirty(UObject* smAsset)
{
	UPackage* smPackage = smAsset->GetOutermost();
	if (smPackage != nullptr)
	{
		smPackage->SetDirtyFlag(true);
	}
}

TMap<FString, UProperty*> UStateMachineBPFunctionLibrary::GetPropertyMap(UObject* smData)
{
	TMap<FString, UProperty*> propertiesMap;
	for (TFieldIterator<UProperty> it(smData->GetClass()); it; ++it)
	{
		propertiesMap.Add(it->GetName(), (*it));
	}
	return propertiesMap;
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime\Core\Public\Modules\ModuleManager.h"
#include "Data/Action/ActionDataBase.h"
#include "Data/Logic/LogicDataBase.h"
#include "Data/Condition/ConditionDataBase.h"
//#include "AssetTools/Public/AssetToolsModule.h"

class FStateMachineModule : public IModuleInterface
{
	/* This will get called when the editor loads the module */
	virtual void StartupModule() override;

	/* This will get called when the editor unloads the module */
	virtual void ShutdownModule() override;

//private:
//	EAssetTypeCategories::Type LogicDataBit;
//	EAssetTypeCategories::Type StateDataBit;
//	EAssetTypeCategories::Type ActionDataBit;
//	EAssetTypeCategories::Type ConditionDataBit;
public:
	TArray<TSubclassOf<UActionDataBase>> GetActionClasses() { return m_ActionClasses; }
	TArray<TSubclassOf<UConditionDataBase>> GetConditionClasses() { return m_ConditionClasses; }
	TArray<TSubclassOf<ULogicDataBase>> GetLogicClasses() { return m_LogicClasses; }

private:
	TArray<TSubclassOf<UActionDataBase>> m_ActionClasses;
	TArray<TSubclassOf<ULogicDataBase>> m_LogicClasses;
	TArray<TSubclassOf<UConditionDataBase>> m_ConditionClasses;
};
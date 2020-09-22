// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectInn.h"
#include "Modules/ModuleManager.h"
#include "StateMachineSingleton.h"
#include "StateMachineImpl/Data/Action/FindCounterAndSetActionData.h"
#include "StateMachineImpl/Data/Action/FindTableAndSetActionData.h"
#include "StateMachineImpl/Data/Action/MoveToLocationActionData.h"
#include "StateMachineImpl/Data/Condition/CheckBBValueConditionData.h"
#include "StateMachineImpl/Data/Condition/IsReachDestinationData.h"

DEFINE_LOG_CATEGORY(LogProjectInn)
DEFINE_LOG_CATEGORY(LogProjectInnStateMachineImpl)

void FProjectInnModule::StartupModule()
{
	UE_LOG(LogProjectInn, Warning, TEXT("Start ProjectInn Module"));

	//IAssetTools& AssetTools = FModuleManager::Get().GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

	//ConditionDataBit = AssetTools.RegisterAdvancedAssetCategory(FName("Condition"), FText::FromString("Condition"));

	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FIsReachDestinationAssetTypeAction(ConditionDataBit)));

	m_ActionClasses.AddUnique(UFindCounterAndSetActionData::StaticClass());
	m_ActionClasses.AddUnique(UFindTableAndSetActionData::StaticClass());
	m_ActionClasses.AddUnique(UMoveToLocationActionData::StaticClass());

	m_ConditionClasses.AddUnique(UCheckBBBoolValueConditionData::StaticClass());
	m_ConditionClasses.AddUnique(UCheckBBIntValueConditionData::StaticClass());
	m_ConditionClasses.AddUnique(UCheckBBF32ValueConditionData::StaticClass());
	m_ConditionClasses.AddUnique(UIsReachDestinationData::StaticClass());	
}

void FProjectInnModule::ShutdownModule()
{
	UE_LOG(LogProjectInn, Warning, TEXT("Shutdown ProjectInn Module"));

	//if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	//{
	//	IAssetTools& AssetTools = FModuleManager::Get().GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

	//	//AssetTools.UnregisterAssetTypeActions(MakeShareable(new FIsReachDestinationAssetTypeAction(ConditionDataBit)));
	//}
}

IMPLEMENT_PRIMARY_GAME_MODULE( FProjectInnModule, ProjectInn, "ProjectInn" );


 
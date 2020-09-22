// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineModule.h"
#include "StateMachineLog.h"
#include "Data/Logic/StepLogicData.h"
#include "Data/Logic/IfElseLogicData.h"
#include "Data/Logic/RepeatLogicData.h"
#include "Data/Condition/ConstConditionData.h"
#include "Data/Condition/TimedConditionData.h"
#include "StateMachineSingleton.h"
//#include "Data/Editor/StateMachineDataDetailCustom.h"
//#include "Data/Editor/TransitionDataDetailCustom.h"
//#include "PropertyEditor/Public/PropertyEditorModule.h"

void FStateMachineModule::StartupModule()
{
	UE_LOG(LogStateMachine, Warning, TEXT("Start StateMachine Module"));

	//IAssetTools& AssetTools = FModuleManager::Get().GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

	//LogicDataBit = AssetTools.RegisterAdvancedAssetCategory(FName("Logic"), FText::FromString("Logic"));

	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FIfElseLogicAssetTypeAction(LogicDataBit)));
	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FRepeatLogicAssetTypeAction(LogicDataBit)));
	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FStepLogicAssetTypeAction(LogicDataBit)));

	//ConditionDataBit = AssetTools.RegisterAdvancedAssetCategory(FName("Condition"), FText::FromString("Condition"));

	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FExpressionConstructorAssetTypeAction(ConditionDataBit)));

	//StateDataBit = AssetTools.RegisterAdvancedAssetCategory(FName("State"), FText::FromString("State"));

	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FStateAssetTypeAction(StateDataBit)));

	//FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//PropertyEditorModule.RegisterCustomClassLayout(FName("StateMachineData"), FOnGetDetailCustomizationInstance::CreateStatic(&StateMachineDataDetailCustom::MakeInstance));
	//PropertyEditorModule.RegisterCustomClassLayout(FName("TransitionData"), FOnGetDetailCustomizationInstance::CreateStatic(&TransitionDataDetailCustom::MakeInstance));

	m_LogicClasses.AddUnique(UStepLogicData::StaticClass());
	m_LogicClasses.AddUnique(UIfElseLogicData::StaticClass());
	m_LogicClasses.AddUnique(URepeatLogicData::StaticClass());

	m_ConditionClasses.AddUnique(UTimedConditionData::StaticClass());
	m_ConditionClasses.AddUnique(UConstConditionData::StaticClass());
}

void FStateMachineModule::ShutdownModule()
{
	UE_LOG(LogStateMachine, Warning, TEXT("Start StateMachine Module"));

	//if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	//{
		//IAssetTools& AssetTools = FModuleManager::Get().GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

		//AssetTools.UnregisterAssetTypeActions(MakeShareable(new FIfElseLogicAssetTypeAction(LogicDataBit)));
		//AssetTools.UnregisterAssetTypeActions(MakeShareable(new FRepeatLogicAssetTypeAction(LogicDataBit)));
		//AssetTools.UnregisterAssetTypeActions(MakeShareable(new FStepLogicAssetTypeAction(LogicDataBit)));

		//AssetTools.UnregisterAssetTypeActions(MakeShareable(new FExpressionConstructorAssetTypeAction(ConditionDataBit)));

		//AssetTools.UnregisterAssetTypeActions(MakeShareable(new FStateAssetTypeAction(StateDataBit)));
	//}

	//FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//PropertyEditorModule.UnregisterCustomClassLayout(FName("StateMachineData"));
	//PropertyEditorModule.UnregisterCustomClassLayout(FName("TransitionData"));
}

IMPLEMENT_MODULE(FStateMachineModule, StateMachineModule);
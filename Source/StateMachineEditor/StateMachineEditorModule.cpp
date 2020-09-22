// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineEditorModule.h"
#include "AssetTypeAction_StateMachineData.h"
#include "StateMachineEditorLog.h"
#include "EdGraphUtilities.h"
#include "Data/State/StateData.h"
#include "Data/State/TransitionData.h"
#include "Data/Action/ActionDataBase.h"
#include "Data/Logic/LogicDataBase.h"
#include "StateMachineGraphNode.h"
#include "StateMachineGraphNode_State.h"
#include "StateMachineGraphNode_Transition.h"
#include "StateMachineGraphNode_Action.h"
#include "StateMachineGraphNode_Logic.h"
#include "SGraphNode_StateMachine.h"
#include "SGraphNode_SMTransition.h"
#include "KismetPins/SGraphPinExec.h"
//#include "Data/Editor/StateMachineDataDetailCustom.h"
//#include "Data/Editor/TransitionDataDetailCustom.h"
//#include "PropertyEditor/Public/PropertyEditorModule.h"

const FName FStateMachineEditorModule::StateMachineEditorAppIdentifier(TEXT("StateMachineEditorApp"));

class FGraphPanelNodeFactory_StateMachine : public FGraphPanelNodeFactory
{
	virtual TSharedPtr<class SGraphNode> CreateNode(UEdGraphNode* Node) const override
	{
		if (UStateMachineGraphNode_State* smNode = Cast<UStateMachineGraphNode_State>(Node))
		{
			return SNew(SGraphNode_StateMachine, smNode);
		}

		else if (UStateMachineGraphNode_Transition* TransitionNode = Cast<UStateMachineGraphNode_Transition>(Node))
		{
			return SNew(SGraphNode_SMTransition, TransitionNode);
		}

		else if (UStateMachineGraphNode_Action* ActionNode = Cast<UStateMachineGraphNode_Action>(Node))
		{
			return SNew(SGraphNode_StateMachine, ActionNode);
		}

		else if (UStateMachineGraphNode_Logic* LogicNode = Cast<UStateMachineGraphNode_Logic>(Node))
		{
			return SNew(SGraphNode_StateMachine, LogicNode);
		}

		return NULL;
	}
};

class FGraphPanelPinFactory_StateMachine : public FGraphPanelPinFactory
{
	virtual TSharedPtr<class SGraphPin> CreatePin(UEdGraphPin* InPin) const override
	{
		//if (UStateMachineGraphNode_State* smNode = Cast<UStateMachineGraphNode_State>(Node))
		//{
		//	return SNew(SGraphNode_StateMachine, smNode);
		//}

		//else if (UStateMachineGraphNode_Transition* TransitionNode = Cast<UStateMachineGraphNode_Transition>(InNode))
		//{
		//	return SNew(SGraphNode_SMTransition, TransitionNode);
		//}

		//return NULL;

		return SNew(SGraphPinExec, InPin);
	}
};

TSharedPtr<FGraphPanelNodeFactory> GraphPanelNodeFactory_StateMachine;
TSharedPtr<FGraphPanelPinFactory> GraphPanelPinFactory_StateMachine;

void FStateMachineEditorModule::StartupModule()
{
	UE_LOG(LogStateMachineEditor, Warning, TEXT("Start StateMachine Editor Module"));

	MenuExtensibilityManager = MakeShareable(new FExtensibilityManager);
	ToolBarExtensibilityManager = MakeShareable(new FExtensibilityManager);

	GraphPanelNodeFactory_StateMachine = MakeShareable(new FGraphPanelNodeFactory_StateMachine());
	FEdGraphUtilities::RegisterVisualNodeFactory(GraphPanelNodeFactory_StateMachine);

	GraphPanelPinFactory_StateMachine = MakeShareable(new FGraphPanelPinFactory());
	FEdGraphUtilities::RegisterVisualPinFactory(GraphPanelPinFactory_StateMachine);

	IAssetTools& AssetTools = FModuleManager::Get().GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

	StateMachineDataBit = AssetTools.RegisterAdvancedAssetCategory(FName("StateMachineData"), FText::FromString("StateMachineData"));

	AssetTools.RegisterAssetTypeActions(MakeShareable(new FAssetTypeAction_StateMachineData(StateMachineDataBit)));
	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FRepeatLogicAssetTypeAction(LogicDataBit)));
	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FStepLogicAssetTypeAction(LogicDataBit)));

	//ConditionDataBit = AssetTools.RegisterAdvancedAssetCategory(FName("Condition"), FText::FromString("Condition"));

	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FExpressionConstructorAssetTypeAction(ConditionDataBit)));

	//StateDataBit = AssetTools.RegisterAdvancedAssetCategory(FName("State"), FText::FromString("State"));

	//AssetTools.RegisterAssetTypeActions(MakeShareable(new FStateAssetTypeAction(StateDataBit)));

	//FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//PropertyEditorModule.RegisterCustomClassLayout(FName("StateMachineData"), FOnGetDetailCustomizationInstance::CreateStatic(&StateMachineDataDetailCustom::MakeInstance));
	//PropertyEditorModule.RegisterCustomClassLayout(FName("TransitionData"), FOnGetDetailCustomizationInstance::CreateStatic(&TransitionDataDetailCustom::MakeInstance));
}

void FStateMachineEditorModule::ShutdownModule()
{
	UE_LOG(LogStateMachineEditor, Warning, TEXT("Shut StateMachine Editor Module"));

	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::Get().GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

		AssetTools.UnregisterAssetTypeActions(MakeShareable(new FAssetTypeAction_StateMachineData(StateMachineDataBit)));
	}

	ActionClassCache.Reset();
	LogicClassCache.Reset();
	StateClassCache.Reset();
	//FPropertyEditorModule& PropertyEditorModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	//PropertyEditorModule.UnregisterCustomClassLayout(FName("StateMachineData"));
	//PropertyEditorModule.UnregisterCustomClassLayout(FName("TransitionData"));
}

TSharedRef<FStateMachineEditor> FStateMachineEditorModule::CreateStateMachineEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UObject* Object)
{
	if (!ActionClassCache.IsValid())
	{
		ActionClassCache = MakeShareable(new FGraphNodeClassHelper(UActionDataBase::StaticClass()));
		ActionClassCache->UpdateAvailableBlueprintClasses();
	}

	if (!LogicClassCache.IsValid())
	{
		LogicClassCache = MakeShareable(new FGraphNodeClassHelper(ULogicDataBase::StaticClass()));
		LogicClassCache->UpdateAvailableBlueprintClasses();
	}

	if (!StateClassCache.IsValid())
	{
		StateClassCache = MakeShareable(new FGraphNodeClassHelper(UStateData::StaticClass()));
		StateClassCache->UpdateAvailableBlueprintClasses();
	}

	if (!TransitionClassCache.IsValid())
	{
		TransitionClassCache = MakeShareable(new FGraphNodeClassHelper(UTransitionData::StaticClass()));
		TransitionClassCache->UpdateAvailableBlueprintClasses();
	}

	TSharedRef< FStateMachineEditor > newStateMachineEditor(new FStateMachineEditor());
	newStateMachineEditor->InitStateMachineEditor(Mode, InitToolkitHost, Object);
	return newStateMachineEditor;
}

IMPLEMENT_MODULE(FStateMachineEditorModule, StateMachineEditorModule);
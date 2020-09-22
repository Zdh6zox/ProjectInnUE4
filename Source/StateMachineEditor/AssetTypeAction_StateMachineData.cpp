// Fill out your copyright notice in the Description page of Project Settings.


#include "AssetTypeAction_StateMachineData.h"
#include "StateMachineEditorModule.h"
#include "Data/StateMachineData.h"

FAssetTypeAction_StateMachineData::FAssetTypeAction_StateMachineData(EAssetTypeCategories::Type InAssetCategory)
	: MyAssetCategory(InAssetCategory)
{
}

uint32 FAssetTypeAction_StateMachineData::GetCategories()
{
	return MyAssetCategory;
}

UClass* FAssetTypeAction_StateMachineData::GetSupportedClass() const
{
	return UStateMachineData::StaticClass();
}

void FAssetTypeAction_StateMachineData::OpenAssetEditor(const TArray<UObject *>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor /* = TSharedPtr<IToolkitHost>() */)
{
	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;

	for (auto Object : InObjects)
	{
		auto stateMachineData = Cast<UStateMachineData>(Object);
		if (stateMachineData != nullptr)
		{
			FStateMachineEditorModule& stateMachineEditorModule = FModuleManager::GetModuleChecked<FStateMachineEditorModule>("StateMachineEditorModule");
			stateMachineEditorModule.CreateStateMachineEditor(Mode, EditWithinLevelEditor, stateMachineData);
		}
	}
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AssetTools/Public/AssetTypeActions_Base.h"

/**
 * 
 */
class STATEMACHINEEDITORMODULE_API FAssetTypeAction_StateMachineData : public FAssetTypeActions_Base
{
public:
	FAssetTypeAction_StateMachineData(EAssetTypeCategories::Type InAssetCategory);
	// IAssetTypeActions Implementation
	virtual FText GetName() const override { return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_StateMachineData", "StateMachineData"); }
	virtual FColor GetTypeColor() const override { return FColor(0, 0, 255); }
	virtual UClass* GetSupportedClass() const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type MyAssetCategory;
};

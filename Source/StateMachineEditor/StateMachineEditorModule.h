// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIGraphTypes.h"
#include "Modules/ModuleInterface.h"
#include "StateMachineEditor.h"
#include "Toolkits/IToolkitHost.h"
#include "Toolkits/AssetEditorToolkit.h"
#include "AssetTypeActions_Base.h"

class FStateMachineEditorModule : public IModuleInterface, public IHasMenuExtensibility, public IHasToolBarExtensibility
{
public:
	/* This will get called when the editor loads the module */
	virtual void StartupModule() override;

	/* This will get called when the editor unloads the module */
	virtual void ShutdownModule() override;

	/** Creates an instance of Behavior Tree editor.  Only virtual so that it can be called across the DLL boundary. */
	virtual TSharedRef<FStateMachineEditor> CreateStateMachineEditor(const EToolkitMode::Type Mode, const TSharedPtr< class IToolkitHost >& InitToolkitHost, class UObject* Object);

	/** Gets the extensibility managers for outside entities to extend static mesh editor's menus and toolbars */
	virtual TSharedPtr<FExtensibilityManager> GetMenuExtensibilityManager() override { return MenuExtensibilityManager; }
	virtual TSharedPtr<FExtensibilityManager> GetToolBarExtensibilityManager() override { return ToolBarExtensibilityManager; }

	/** Behavior Tree app identifier string */
	static const FName StateMachineEditorAppIdentifier;

	TSharedPtr<struct FGraphNodeClassHelper> GetStateClassCache() { return StateClassCache; }
	TSharedPtr<struct FGraphNodeClassHelper> GetTransitionClassCache() { return TransitionClassCache; }
	TSharedPtr<struct FGraphNodeClassHelper> GetActionClassCache() { return ActionClassCache; }
	TSharedPtr<struct FGraphNodeClassHelper> GetLogicClassCache() { return LogicClassCache; }

private:
	TSharedPtr<FExtensibilityManager> MenuExtensibilityManager;
	TSharedPtr<FExtensibilityManager> ToolBarExtensibilityManager;

	EAssetTypeCategories::Type StateMachineDataBit;

	TSharedPtr<struct FGraphNodeClassHelper> StateClassCache;
	TSharedPtr<struct FGraphNodeClassHelper> TransitionClassCache;
	TSharedPtr<struct FGraphNodeClassHelper> ActionClassCache;
	TSharedPtr<struct FGraphNodeClassHelper> LogicClassCache;
};
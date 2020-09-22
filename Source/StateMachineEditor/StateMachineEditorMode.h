// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Docking/TabManager.h"
#include "StateMachineEditor.h"
#include "WorkflowOrientedApp/WorkflowTabManager.h"
#include "WorkflowOrientedApp/ApplicationMode.h"
/**
 * 
 */
class STATEMACHINEEDITORMODULE_API FStateMachineEditorApplicationMode : public FApplicationMode
{
public:
	FStateMachineEditorApplicationMode(TSharedPtr<class FStateMachineEditor> InStateMachineEditor);

	virtual void RegisterTabFactories(TSharedPtr<class FTabManager> InTabManager) override;
	virtual void PreDeactivateMode() override;
	virtual void PostActivateMode() override;

protected:
	TWeakPtr<class FStateMachineEditor> m_StateMachineEditor;

	// Set of spawnable tabs in behavior tree editing mode
	FWorkflowAllowedTabSet m_StateMachineEditorTabFactories;
};

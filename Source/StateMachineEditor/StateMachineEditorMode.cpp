// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineEditorMode.h"
#include "StateMachineEditorTabFactories.h"
#include "Toolkits/IToolkit.h"

FStateMachineEditorApplicationMode::FStateMachineEditorApplicationMode(TSharedPtr<class FStateMachineEditor> InStateMachineEditor)
	: FApplicationMode("StateMachineData")
{
	m_StateMachineEditor = InStateMachineEditor;

	m_StateMachineEditorTabFactories.RegisterFactory(MakeShareable(new FStateDetailsSummoner(InStateMachineEditor)));

	TabLayout = FTabManager::NewLayout("Standalone_BehaviorTree_Layout_v1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.1f)
				->AddTab(InStateMachineEditor->GetToolbarTabId(), ETabState::OpenedTab)
				->SetHideTabWell(true)
			)
			->Split
			(
				FTabManager::NewSplitter()->SetOrientation(Orient_Horizontal)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.7f)
					->AddTab(TEXT("StateMachineData_Graph"), ETabState::ClosedTab)
				)
				->Split
				(
					FTabManager::NewSplitter()->SetOrientation(Orient_Vertical)
					->SetSizeCoefficient(0.3f)
					->Split
					(
						FTabManager::NewStack()
						->SetSizeCoefficient(0.6f)
						->AddTab(TEXT("StateData_Properties"), ETabState::OpenedTab)
					)
				)
			)
		);

	//InStateMachineEditor->GetToolbarBuilder()->AddModesToolbar(ToolbarExtender);
	//InStateMachineEditor->GetToolbarBuilder()->AddDebuggerToolbar(ToolbarExtender);
	//InStateMachineEditor->GetToolbarBuilder()->AddBehaviorTreeToolbar(ToolbarExtender);
}

void FStateMachineEditorApplicationMode::RegisterTabFactories(TSharedPtr<FTabManager> InTabManager)
{
	check(m_StateMachineEditor.IsValid());
	TSharedPtr<FStateMachineEditor> stataMachineEditorPtr = m_StateMachineEditor.Pin();

	stataMachineEditorPtr->RegisterToolbarTab(InTabManager.ToSharedRef());

	// Mode-specific setup
	stataMachineEditorPtr->PushTabFactories(m_StateMachineEditorTabFactories);

	FApplicationMode::RegisterTabFactories(InTabManager);
}

void FStateMachineEditorApplicationMode::PreDeactivateMode()
{
	FApplicationMode::PreDeactivateMode();

	check(m_StateMachineEditor.IsValid());
	TSharedPtr<FStateMachineEditor> stataMachineEditorPtr = m_StateMachineEditor.Pin();

	stataMachineEditorPtr->SaveEditedObjectState();
}

void FStateMachineEditorApplicationMode::PostActivateMode()
{
	// Reopen any documents that were open when the blueprint was last saved
	check(m_StateMachineEditor.IsValid());
	TSharedPtr<FStateMachineEditor> stataMachineEditorPtr = m_StateMachineEditor.Pin();
	stataMachineEditorPtr->RestoreStateMachine();

	FApplicationMode::PostActivateMode();
}
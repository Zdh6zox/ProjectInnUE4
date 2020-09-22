// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineEditorTabFactories.h"
#include "Widgets/Docking/SDockTab.h"

FStateDetailsSummoner::FStateDetailsSummoner(TSharedPtr<class FStateMachineEditor> InStateMachineEditorPtr)
	: FWorkflowTabFactory(TEXT("StateData_Properties"), InStateMachineEditorPtr)
	, StateMachineEditorPtr(InStateMachineEditorPtr)
{
	TabLabel = FText::FromString("Details");
	TabIcon = FSlateIcon(FEditorStyle::GetStyleSetName(), "Kismet.Tabs.Components");

	bIsSingleton = true;
}

TSharedRef<SWidget> FStateDetailsSummoner::CreateTabBody(const FWorkflowTabSpawnInfo& Info) const
{
	check(StateMachineEditorPtr.IsValid());
	return StateMachineEditorPtr.Pin()->SpawnProperties();
}

FText FStateDetailsSummoner::GetTabToolTipText(const FWorkflowTabSpawnInfo& Info) const
{
	FText text;
	text.FromString("Testing State Tab Details ToolTip");
	return text;
}

FSMGraphEditorSummoner::FSMGraphEditorSummoner(TSharedPtr<class FStateMachineEditor> InStateMachineEditorPtr, FOnCreateGraphEditorWidget CreateGraphEditorWidgetCallback)
	: FDocumentTabFactoryForObjects<UEdGraph>(TEXT("StateMachineData_Graph"), InStateMachineEditorPtr)
	, StateMachineEditorPtr(InStateMachineEditorPtr)
	, OnCreateGraphEditorWidget(CreateGraphEditorWidgetCallback)
{
}

void FSMGraphEditorSummoner::OnTabActivated(TSharedPtr<SDockTab> Tab) const
{
	check(StateMachineEditorPtr.IsValid());
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	StateMachineEditorPtr.Pin()->OnGraphEditorFocused(GraphEditor);
}

void FSMGraphEditorSummoner::OnTabRefreshed(TSharedPtr<SDockTab> Tab) const
{
	TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());
	GraphEditor->NotifyGraphChanged();
}

TAttribute<FText> FSMGraphEditorSummoner::ConstructTabNameForObject(UEdGraph* DocumentID) const
{
	return TAttribute<FText>(FText::FromString(DocumentID->GetName()));
}

TSharedRef<SWidget> FSMGraphEditorSummoner::CreateTabBodyForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const
{
	return OnCreateGraphEditorWidget.Execute(DocumentID);
}

const FSlateBrush* FSMGraphEditorSummoner::GetTabIconForObject(const FWorkflowTabSpawnInfo& Info, UEdGraph* DocumentID) const
{
	return FEditorStyle::GetBrush("NoBrush");
}

void FSMGraphEditorSummoner::SaveState(TSharedPtr<SDockTab> Tab, TSharedPtr<FTabPayload> Payload) const
{

	//check(BehaviorTreeEditorPtr.IsValid());
	//check(BehaviorTreeEditorPtr.Pin()->GetBehaviorTree());

	//TSharedRef<SGraphEditor> GraphEditor = StaticCastSharedRef<SGraphEditor>(Tab->GetContent());

	//FVector2D ViewLocation;
	//float ZoomAmount;
	//GraphEditor->GetViewLocation(ViewLocation, ZoomAmount);

	//UEdGraph* Graph = FTabPayload_UObject::CastChecked<UEdGraph>(Payload);
	//StateMachineEditorPtr.Pin()->GetBehaviorTree()->LastEditedDocuments.Add(FEditedDocumentInfo(Graph, ViewLocation, ZoomAmount));
}
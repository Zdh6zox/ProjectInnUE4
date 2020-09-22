// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineGraphNode.h"
#include "ToolMenus.h"
#include "AIGraph/Public/SGraphEditorActionMenuAI.h"
#include "StateMachineEditorTypes.h"
#include "Data/Action/ActionDataBase.h"
#include "Data/Logic/LogicDataBase.h"

#define LOCTEXT_NAMESPACE "StateMachineEditor"

UStateMachineGraphNode::UStateMachineGraphNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UStateMachineGraphNode::CreateAddEnterActionSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const
{
	TSharedRef<SGraphEditorActionMenuAI> Widget =
		SNew(SGraphEditorActionMenuAI)
		.GraphObj(Graph)
		.GraphNode((UStateMachineGraphNode*)this)
		.SubNodeFlags(EStateSubNode::EnterAction)
		.AutoExpandActionMenu(true);

	FToolMenuSection& Section = Menu->FindOrAddSection("Section");
	Section.AddEntry(FToolMenuEntry::InitWidget("ActionWidget", Widget, FText(), true));
}

void UStateMachineGraphNode::CreateAddExitActionSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const
{
	TSharedRef<SGraphEditorActionMenuAI> Widget =
		SNew(SGraphEditorActionMenuAI)
		.GraphObj(Graph)
		.GraphNode((UStateMachineGraphNode*)this)
		.SubNodeFlags(EStateSubNode::ExitAction)
		.AutoExpandActionMenu(true);

	FToolMenuSection& Section = Menu->FindOrAddSection("Section");
	Section.AddEntry(FToolMenuEntry::InitWidget("ActionWidget", Widget, FText(), true));
}

void UStateMachineGraphNode::CreateAddLogicSubMenu(class UToolMenu* Menu, UEdGraph* Graph) const
{
	TSharedRef<SGraphEditorActionMenuAI> Widget =
		SNew(SGraphEditorActionMenuAI)
		.GraphObj(Graph)
		.GraphNode((UStateMachineGraphNode*)this)
		.SubNodeFlags(EStateSubNode::Logic)
		.AutoExpandActionMenu(true);

	FToolMenuSection& Section = Menu->FindOrAddSection("Section");
	Section.AddEntry(FToolMenuEntry::InitWidget("LogicWidget", Widget, FText(), true));
}

void UStateMachineGraphNode::AddContextMenuActionsEnterActions(class UToolMenu* Menu, const FName SectionName, class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->FindOrAddSection(SectionName);
	Section.AddSubMenu(
		"AddEnterAction",
		LOCTEXT("AddEnterAction", "Add Enter Action..."),
		LOCTEXT("AddEnterActionTooltip", "Adds new enter action as a subnode"),
		FNewToolMenuDelegate::CreateUObject(this, &UStateMachineGraphNode::CreateAddEnterActionSubMenu, (UEdGraph*)Context->Graph));
}

void UStateMachineGraphNode::AddContextMenuActionsExitActions(class UToolMenu* Menu, const FName SectionName, class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->FindOrAddSection(SectionName);
	Section.AddSubMenu(
		"AddExitAction",
		LOCTEXT("AddExitAction", "Add Exit Action..."),
		LOCTEXT("AddExitActionTooltip", "Adds new exit action as a subnode"),
		FNewToolMenuDelegate::CreateUObject(this, &UStateMachineGraphNode::CreateAddExitActionSubMenu, (UEdGraph*)Context->Graph));
}

void UStateMachineGraphNode::AddContextMenuActionsLogics(class UToolMenu* Menu, const FName SectionName, class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->FindOrAddSection(SectionName);
	Section.AddSubMenu(
		"AddLogic",
		FText::FromString("Add Logic..."),
		FText::FromString("Adds new logic"),
		FNewToolMenuDelegate::CreateUObject(this, &UStateMachineGraphNode::CreateAddLogicSubMenu, (UEdGraph*)Context->Graph));
}

//int32 UStateMachineGraphNode::FindSubNodeDropIndex(UAIGraphNode* SubNode) const
//{
//	const int32 SubIdx = SubNodes.IndexOfByKey(SubNode) + 1;
//	const int32 EnterActionIdx = EnterActions.IndexOfByKey(SubNode) + 1;
//	const int32 ExitActionIdx = ExitActions.IndexOfByKey(SubNode) + 1;
//	const int32 LogicIdx = Logics.IndexOfByKey(SubNode) + 1;
//
//	const int32 CombinedIdx = (SubIdx & 0xff) | ((EnterActionIdx & 0xff) << 8) | ((LogicIdx & 0xff) << 16);
//	return CombinedIdx;
//}
//
//void UStateMachineGraphNode::InsertSubNodeAt(UAIGraphNode* SubNode, int32 DropIndex)
//{
//	const int32 SubIdx = (DropIndex & 0xff) - 1;
//	const int32 EnterActionIdx = ((DropIndex >> 8) & 0xff) - 1;
//	const int32 ExitActionIdx = ((DropIndex >> 16) & 0xff) - 1;
//	const int32 LogicIdx = ((DropIndex >> 16) & 0xff) - 1;
//
//	if (SubIdx >= 0)
//	{
//		SubNodes.Insert(SubNode, SubIdx);
//	}
//	else
//	{
//		SubNodes.Add(SubNode);
//	}
//
//	UStateMachineGraphNode* TypedNode = Cast<UStateMachineGraphNode>(SubNode);
//	const bool bIsAction = Cast<UActionDataBase>(SubNode->NodeInstance) != nullptr;
//	const bool bIsLogic = Cast<ULogicDataBase>(SubNode->NodeInstance) != nullptr;
//
//	if (TypedNode)
//	{
//		if (bIsAction)
//		{
//			if (EnterActionIdx >= 0)
//			{
//				EnterActions.Insert(TypedNode, EnterActionIdx);
//			}
//			else
//			{
//				EnterActions.Add(TypedNode);
//			}
//
//		}
//
//		if (bIsLogic)
//		{
//			if (LogicIdx >= 0)
//			{
//				Logics.Insert(TypedNode, LogicIdx);
//			}
//			else
//			{
//				Logics.Add(TypedNode);
//			}
//		}
//	}
//}

#undef LOCTEXT_NAMESPACE
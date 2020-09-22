// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Layout/Visibility.h"
#include "Styling/SlateColor.h"
#include "Input/Reply.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "SNodePanel.h"
#include "SGraphNode.h"
#include "SGraphPin.h"
#include "SGraphNodeAI.h"
/**
 * 
 */
class SHorizontalBox;
class SToolTip;
class SVerticalBox;
class UStateMachineGraphNode;

class SGraphNode_StateMachine : public SGraphNodeAI
{
public:
	SLATE_BEGIN_ARGS(SGraphNode_StateMachine) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UStateMachineGraphNode* InNode);

	// SGraphNode interface
	virtual void UpdateGraphNode() override;
	virtual void CreatePinWidgets() override;
	virtual void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	virtual TSharedPtr<SToolTip> GetComplexTooltip() override;
	virtual void GetOverlayBrushes(bool bSelected, const FVector2D WidgetSize, TArray<FOverlayBrushInfo>& Brushes) const override;
	virtual TArray<FOverlayWidgetInfo> GetOverlayWidgets(bool bSelected, const FVector2D& WidgetSize) const override;
	virtual TSharedRef<SGraphNode> GetNodeUnderMouse(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void MoveTo(const FVector2D& NewPosition, FNodeSet& NodeFilter) override;
	// End of SGraphNode interface

		/**
	 * Ticks this widget.  Override in derived classes, but always call the parent implementation.
	 *
	 * @param  AllottedGeometry The space allotted for this widget
	 * @param  InCurrentTime  Current absolute real time
	 * @param  InDeltaTime  Real time passed since last tick
	 */
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;

	/** adds enter action widget inside current node */
	void AddEnterAction(TSharedPtr<SGraphNode> ActionWidget);

	/** adds enter action widget inside current node */
	void AddExitAction(TSharedPtr<SGraphNode> ActionWidget);

	/** adds logic widget inside current node */
	void AddLogic(TSharedPtr<SGraphNode> LogicWidget);

	//void AddTransition(TSharedPtr<SGraphNode> TransWidget);

	FText GetPinTooltip(UEdGraphPin* GraphPinObj) const;

	EVisibility GetNameVisibility() const;

protected:
	TArray< TSharedPtr<SGraphNode> > EnterActionWidgets;
	TArray< TSharedPtr<SGraphNode> > ExitActionWidgets;
	TArray< TSharedPtr<SGraphNode> > LogicWidgets;
	TArray< TSharedPtr<SGraphNode> > TransWidgets;
	TSharedPtr<SVerticalBox> EnterActionsBox;
	TSharedPtr<SVerticalBox> ExitActionsBox;
	TSharedPtr<SVerticalBox> LogicsBox;
	TSharedPtr<SHorizontalBox> OutputPinBox;

	/** The node body widget, cached here so we can determine its size when we want ot position our overlays */
	TSharedPtr<SBorder> NodeBody;
};

class SStateMachinePin : public SGraphPinAI
{
public:
	SLATE_BEGIN_ARGS(SStateMachinePin) {}
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);

protected:
	/** @return The color that we should use to draw this pin */
	virtual FSlateColor GetPinColor() const override;
};

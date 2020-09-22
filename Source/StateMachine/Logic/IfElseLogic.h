// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/LogicBase.h"

class FConditionBase;
class FActionBase;
/**
 * 
 */
class FIfElseLogic : public FLogicBase
{
public:
	FIfElseLogic();
	~FIfElseLogic();

	virtual void StartLogic(TWeakPtr<FActionExecutionContext> ctx) override;
	virtual void UpdateLogic(TWeakPtr<FActionExecutionContext> ctx) override;

	void SetCondition(TSharedPtr<FConditionBase> condition) { m_Condition = condition; }

private:
	TSharedPtr<FConditionBase> m_Condition;
	TSharedPtr<FActionBase> m_PositiveAction;
	TSharedPtr<FActionBase> m_NegativeAction;
};

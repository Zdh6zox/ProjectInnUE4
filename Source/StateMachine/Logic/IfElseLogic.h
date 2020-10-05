// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/LogicBase.h"

class FActionBase;
class FExpression;
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

	void SetPositiveAction(FActionBase* action);
	void SetNegativeAction(FActionBase* action);
	void SetExpression(FExpression* expression);

private:
	TSharedPtr<FExpression> m_Expression;
	TSharedPtr<FActionBase> m_PositiveAction;
	TSharedPtr<FActionBase> m_NegativeAction;
};

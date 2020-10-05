// Fill out your copyright notice in the Description page of Project Settings.


#include "IfElseLogicData.h"
#include "Logic/IfElseLogic.h"
#include "Data/Condition/ExpressionData.h"
#include "Data/Action/ActionDataBase.h"

FLogicBase* UIfElseLogicData::ConstructLogic()
{
	FIfElseLogic* ifElseLogic = new FIfElseLogic();

	if (PositiveAction != NULL)
	{
		FActionBase* positiveAction = PositiveAction->CreateAction();
		ifElseLogic->SetPositiveAction(positiveAction);
	}

	if (NegativeAction != NULL)
	{
		FActionBase* negativeAction = NegativeAction->CreateAction();
		ifElseLogic->SetPositiveAction(negativeAction);
	}

	FExpression* expression = Expression.CreateExpression();
	ifElseLogic->SetExpression(expression);

	return ifElseLogic;
}
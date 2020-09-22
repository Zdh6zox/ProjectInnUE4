// Fill out your copyright notice in the Description page of Project Settings.


#include "Transition.h"
#include "State/State.h"
#include "Condition/Expression.h"

FTransition::FTransition()
{
}

FTransition::~FTransition()
{
}

bool FTransition::IsValid(UStateMachineComponent* owner)
{
	return m_Expression->GetExpressionResult(owner);
}

void FTransition::SetExpression(FExpression* expression)
{
	m_Expression = MakeShareable(expression);
}
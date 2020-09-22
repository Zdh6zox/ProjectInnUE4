// Fill out your copyright notice in the Description page of Project Settings.


#include "TransitionData.h"
#include "StateData.h"
#include "State/Transition.h"

FTransition* UTransitionData::CreateTransition()
{
	FTransition* newTrans = new FTransition();

	newTrans->SetExpression(Expression.CreateExpression());

	return newTrans;
}
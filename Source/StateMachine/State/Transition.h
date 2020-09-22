// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class FState;
class FExpression;
class UStateMachineComponent;

class FTransition
{
public:
	FTransition();
	~FTransition();

	bool IsValid(UStateMachineComponent* owner);
	TWeakPtr<FState> GetNextState() { return m_NextState; }
	void SetNextState(TSharedPtr<FState> nextState) { m_NextState = nextState; }
	void SetExpression(FExpression* expression);

private:
	TWeakPtr<FState> m_NextState;
	TSharedPtr<FExpression> m_Expression;
};

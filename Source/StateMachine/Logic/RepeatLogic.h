// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/LogicBase.h"

/**
 * 
 */
class STATEMACHINEMODULE_API FRepeatLogic : public FLogicBase
{
public:
	virtual void StartLogic(TWeakPtr<FActionExecutionContext> ctx) override;
	virtual void UpdateLogic(TWeakPtr<FActionExecutionContext> ctx) override;
};

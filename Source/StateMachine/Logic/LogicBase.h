// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class FActionExecutionContext;

UENUM(BlueprintType)
enum class ELogicStatus : uint8
{
	Onhold,
	Running,
	Finished
};

/**
 * 
 */

class FLogicBase
{
public:
	FLogicBase();
	virtual ~FLogicBase();

	virtual void StartLogic(TWeakPtr<FActionExecutionContext> ctx) {}
	virtual void UpdateLogic(TWeakPtr<FActionExecutionContext> ctx) {}
	ELogicStatus GetLogicStatus() { return m_LogicStatus; }

protected:
	FString m_LogicName;
	ELogicStatus m_LogicStatus = ELogicStatus::Onhold;
};

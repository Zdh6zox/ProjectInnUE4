// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"

/**
 * 
 */
class PROJECTINN_API FMoveToLocationAction : public FActionBase
{
public:
	typedef FActionBase super;
	FMoveToLocationAction(FString actionName, FName locationKey, float isReachThreshold, bool objectAsDest);
	~FMoveToLocationAction();

	virtual void Init(TWeakPtr<FActionExecutionContext> ctx) override;
	virtual void Execute(TWeakPtr<FActionExecutionContext> ctx) override;

private:
	FName m_LocationKey;
	bool m_ObjectAsDest;
	float m_IsReachThreshold;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/ActionBase.h"
/**
 * 
 */
class PROJECTINN_API FFindTableAndSetAction : public FActionBase
{
public:
	typedef FActionBase super;
	FFindTableAndSetAction(FString actionName, FName keyToStore);
	virtual void Init(TWeakPtr<FActionExecutionContext> ctx) override;
	virtual void Execute(TWeakPtr<FActionExecutionContext> ctx) override;

private:
	FName m_KeyToStore;
};

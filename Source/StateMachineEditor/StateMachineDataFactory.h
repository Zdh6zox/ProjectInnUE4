// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "StateMachineDataFactory.generated.h"

/**
 * 
 */
UCLASS()
class STATEMACHINEEDITORMODULE_API UStateMachineDataFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UStateMachineDataFactory(const class FObjectInitializer& ObjectInitializer);
	// UFactory interface
	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	virtual bool CanCreateNew() const override;
	// End of UFactory interface
};

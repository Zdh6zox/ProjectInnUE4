// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineDataFactory.h"
#include "Data/StateMachineData.h"

UStateMachineDataFactory::UStateMachineDataFactory(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer) {
	SupportedClass = UStateMachineData::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

bool UStateMachineDataFactory::CanCreateNew() const
{
	return true;
}

UObject* UStateMachineDataFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UStateMachineData::StaticClass()));
	return NewObject<UStateMachineData>(InParent, Class, Name, Flags);;
}
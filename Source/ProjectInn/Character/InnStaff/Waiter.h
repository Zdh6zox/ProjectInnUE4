// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/NonPlayerCharacter.h"
#include "WaiterData.h"
#include "Waiter.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINN_API AWaiter : public ANonPlayerCharacter
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		FWaiterData WaiterData;

private:
	TSharedPtr<FWaiterDataRuntime> m_RuntimeData;
};

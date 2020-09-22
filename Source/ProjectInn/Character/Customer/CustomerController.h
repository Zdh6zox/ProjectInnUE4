// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINN_API ACustomerController : public AAIController
{
	GENERATED_BODY()
	
public:
	void MoveToPosition(FVector position);
	bool IsMovingTo(FVector position);
	bool IsMoveCompleted(FVector position);
};

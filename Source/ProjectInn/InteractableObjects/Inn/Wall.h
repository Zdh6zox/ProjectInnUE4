// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects/Inn/ConstructableObject.h"
#include "SharedEnumTypes.h"
#include "Wall.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINN_API AWall : public AConstructableObject
{
	GENERATED_BODY()
	
public:

public:
	UFUNCTION(BlueprintImplementableEvent)
		void ToggleCollision_BP(bool enable);

	virtual void ToggleCollision(bool enable);
};

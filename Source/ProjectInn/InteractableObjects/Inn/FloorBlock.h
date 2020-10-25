// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableObjects/Inn/ConstructableObject.h"
#include "SharedEnumTypes.h"
#include "FloorBlock.generated.h"

/**
 * 
 */
class AWall;

UCLASS()
class PROJECTINN_API AFloorBlock : public AConstructableObject
{
	GENERATED_BODY()
	
public:
	AFloorBlock();

	UPROPERTY(EditAnywhere)
		EFloorBlockMaterial BlockMaterial = EFloorBlockMaterial::Mud;

	UPROPERTY(EditAnywhere)
		int FloorLayer;

	UPROPERTY(EditAnywhere)
		EFloorBlockLocationType BlockLocationType = EFloorBlockLocationType::None;

	UFUNCTION(BlueprintImplementableEvent)
		void ToggleCollision_BP(bool enable);

	void ConstructWall(int wallLevel);

	void InitializeBlockWithMaterial(EFloorBlockMaterial matType);

	virtual void ToggleCollision(bool enable);

	UFUNCTION(BlueprintCallable)
		void Test_ConstructWall(int level);
public:

	UPROPERTY()
		TArray<AWall*> Walls;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorBlock.h"
#include "Manager/GameManager.h"

AFloorBlock::AFloorBlock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AFloorBlock::InitializeBlockWithMaterial(EFloorBlockMaterial matType)
{
	BlockMaterial = matType;

	AGameManager::GetGameManager(GetWorld())->GetInnManager();
}

void AFloorBlock::ToggleCollision(bool enable)
{
	ToggleCollision_BP(enable);
}
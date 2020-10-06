// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorBlock.h"
#include "Manager/GameManager.h"

void AFloorBlock::InitializeBlockWithMaterial(EFloorBlockMaterial matType)
{
	BlockMaterial = matType;

	AGameManager::GetGameManager(GetWorld())->GetInnManager();
}
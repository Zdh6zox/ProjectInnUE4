// Fill out your copyright notice in the Description page of Project Settings.


#include "FloorBlock.h"
#include "Manager/GameManager.h"
#include "InteractableObjects/Inn/Wall.h"

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

void AFloorBlock::ConstructWall(int wallLevel)
{
	UWorld* world = GetWorld();
	Walls.Empty();

	//construct wall according to location type
	switch (BlockLocationType)
	{
	case EFloorBlockLocationType::Top:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWall = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWall->AddActorWorldOffset(FVector(100.0f, 0.f, 0.f));
		Walls.Add(spawnedWall);
		break;
	}
	case EFloorBlockLocationType::Bottom:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWall = world->SpawnActor<AWall>(wallClass, spawnTrans);
		Walls.Add(spawnedWall);
		break;
	}
	case EFloorBlockLocationType::Left:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWall = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWall->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		Walls.Add(spawnedWall);
		break;
	}
	case EFloorBlockLocationType::Right:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWall = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWall->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		spawnedWall->AddActorWorldOffset(FVector(0.f, 100.f, 0.f));
		Walls.Add(spawnedWall);
		break;
	}
	case EFloorBlockLocationType::TopLeftCorner:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWallTop = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallTop->AddActorWorldOffset(FVector(100.0f, 0.f, 0.f));
		Walls.Add(spawnedWallTop);

		AWall* spawnedWallLeft = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallLeft->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		Walls.Add(spawnedWallLeft);
		break;
	}
	case EFloorBlockLocationType::TopRightCorner:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWallTop = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallTop->AddActorWorldOffset(FVector(100.0f, 0.f, 0.f));
		Walls.Add(spawnedWallTop);

		AWall* spawnedWallRight = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallRight->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		spawnedWallRight->AddActorWorldOffset(FVector(0.f, 100.f, 0.f));
		Walls.Add(spawnedWallRight);
		break;
	}
	case EFloorBlockLocationType::BottomLeftCorner:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWallBottom = world->SpawnActor<AWall>(wallClass, spawnTrans);
		Walls.Add(spawnedWallBottom);

		AWall* spawnedWallLeft = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallLeft->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		Walls.Add(spawnedWallLeft);
		break;
	}
	case EFloorBlockLocationType::BottomRightCorner:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWallBottom = world->SpawnActor<AWall>(wallClass, spawnTrans);
		Walls.Add(spawnedWallBottom);

		AWall* spawnedWallRight = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallRight->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		spawnedWallRight->AddActorWorldOffset(FVector(0.f, 100.f, 0.f));
		Walls.Add(spawnedWallRight);
		break;
	}
	case EFloorBlockLocationType::TopMost:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWallTop = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallTop->AddActorWorldOffset(FVector(100.0f, 0.f, 0.f));
		Walls.Add(spawnedWallTop);

		AWall* spawnedWallLeft = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallLeft->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		Walls.Add(spawnedWallLeft);

		AWall* spawnedWallRight = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallRight->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		spawnedWallRight->AddActorWorldOffset(FVector(0.f, 100.f, 0.f));
		Walls.Add(spawnedWallRight);
		break;
	}
	case EFloorBlockLocationType::BottomMost:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWallBottom = world->SpawnActor<AWall>(wallClass, spawnTrans);
		Walls.Add(spawnedWallBottom);

		AWall* spawnedWallLeft = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallLeft->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		Walls.Add(spawnedWallLeft);

		AWall* spawnedWallRight = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallRight->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		spawnedWallRight->AddActorWorldOffset(FVector(0.f, 100.f, 0.f));
		Walls.Add(spawnedWallRight);
		break;
	}
	case EFloorBlockLocationType::LeftMost:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWallTop = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallTop->AddActorWorldOffset(FVector(100.0f, 0.f, 0.f));
		Walls.Add(spawnedWallTop);

		AWall* spawnedWallBottom = world->SpawnActor<AWall>(wallClass, spawnTrans);
		Walls.Add(spawnedWallBottom);

		AWall* spawnedWallLeft = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallLeft->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		Walls.Add(spawnedWallLeft);
		break;
	}
	case EFloorBlockLocationType::RightMost:
	{
		TSubclassOf<AConstructableObject> wallClass = AGameManager::GetGameManager(world)->GetInnManager().LoadClassViaTypeAndLevel(EConstructableObjectType::Wall, wallLevel);
		FTransform spawnTrans = GetTransform();
		AWall* spawnedWallTop = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallTop->AddActorWorldOffset(FVector(100.0f, 0.f, 0.f));
		Walls.Add(spawnedWallTop);

		AWall* spawnedWallBottom = world->SpawnActor<AWall>(wallClass, spawnTrans);
		Walls.Add(spawnedWallBottom);

		AWall* spawnedWallRight = world->SpawnActor<AWall>(wallClass, spawnTrans);
		spawnedWallRight->AddActorWorldRotation(FRotator(0.f, -90.f, 0.f));
		spawnedWallRight->AddActorWorldOffset(FVector(0.f, 100.f, 0.f));
		Walls.Add(spawnedWallRight);
		break;
	}
	case EFloorBlockLocationType::None:
		break;
	default:
		break;
	}
}

void AFloorBlock::Test_ConstructWall(int level)
{
	ConstructWall(level);
}
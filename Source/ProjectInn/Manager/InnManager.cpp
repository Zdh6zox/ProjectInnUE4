// Fill out your copyright notice in the Description page of Project Settings.


#include "InnManager.h"
#include "Inndata.h"
#include "Manager/GameManager.h"
#include "ProjectInn.h"
#include "InteractableObjects/Inn/Table.h"
#include "InteractableObjects/Inn/TableSearchRequest.h"
#include "InteractableObjects/Inn/Counter.h"
#include "InteractableObjects/Inn/FloorBlock.h"
#include "InteractableObjects/Inn/BaseBlock.h"
#include "Materials/Material.h"
#include "UObject/ConstructorHelpers.h"
#include "ProjectInnPlayerController.h"
#include "Kismet/GameplayStatics.h"


void FInnManager::InitializeManager(AGameManager* gm)
{
	m_GameManager = MakeWeakObjectPtr(gm);

	m_TableClass = gm->TableTemplate;
	if (m_TableClass == nullptr)
	{
		UE_LOG(LogProjectInn, Error, TEXT("Miss setup table class in Game Manager"));
	}
	m_FloorBlockClass = gm->FloorBlockTemplate;
	if (m_FloorBlockClass == nullptr)
	{
		UE_LOG(LogProjectInn, Error, TEXT("Miss setup floor block class in Game Manager"));
	}
	//Search available save data
	USaveGame* saveGame = UGameplayStatics::LoadGameFromSlot("Slot1", 0);
	if (saveGame != nullptr)
	{
		m_CurrentInnSaveData = Cast<UInnData>(saveGame);
	}
	else
	{
		UE_LOG(LogProjectInn, Error, TEXT("Cannot load from slot1"));
	}

	//Clear out old data
	m_CurrentTables.Empty();
	m_BaseBlocks.Empty();

	m_CurrentSelectedClass = NULL;
	m_CurrentDisplayObject = NULL;
	m_CurrentMode = EInnManagerMode::Normal;

	TArray<AActor*> foundBaseBlocks;
	UGameplayStatics::GetAllActorsOfClass(m_GameManager.Get(), ABaseBlock::StaticClass(), foundBaseBlocks);

	for (int i = 0; i < foundBaseBlocks.Num(); ++i)
	{
		ABaseBlock* baseBlock = Cast<ABaseBlock>(foundBaseBlocks[i]);
		m_BaseBlocks.Add(baseBlock);
	}
}

void FInnManager::SaveGame(FString slotName)
{
	if (m_CurrentInnSaveData == nullptr)
	{
		m_CurrentInnSaveData = NewObject<UInnData>();
	}

	UGameplayStatics::SaveGameToSlot(m_CurrentInnSaveData, slotName, 0);
}

void FInnManager::RegisterCounter(ACounter* counter)
{
	m_Counter = counter;
}

ACounter* FInnManager::FindCounter()
{
	return m_Counter.Get();
}

void FInnManager::SpawnTables()
{
	if (m_CurrentInnSaveData == nullptr)
	{
		UE_LOG(LogProjectInn, Error, TEXT("Current save is null"));
		return;
	}

	UWorld* world = m_GameManager->GetAssociatedWorld();
	for (int i = 0; i < m_CurrentInnSaveData->Tables.Num(); ++i)
	{
		FTransform tableTrans = m_CurrentInnSaveData->Tables[i].TableTransform;

		
		ATable* spawnedTable = world->SpawnActor<ATable>(m_TableClass, tableTrans.GetLocation(), tableTrans.GetRotation().Rotator());
		spawnedTable->InitializeTable(m_CurrentInnSaveData->Tables[i]);
		//m_CurrentTables.Add(spawnedTable);
	}
}

void FInnManager::Tick()
{
	if (m_CurrentMode == EInnManagerMode::Construct)
	{
		UpdateConstructMode();
	}
}

void FInnManager::UpdateConstructMode()
{
	AProjectInnPlayerController* controller = Cast<AProjectInnPlayerController>(UGameplayStatics::GetPlayerController(m_GameManager.Get(), 0));
	if (m_CurrentDisplayObject == NULL && m_CurrentSelectedClass != NULL)
	{
		UWorld* world = m_GameManager->GetAssociatedWorld();
		FTransform spawnTrans;
		spawnTrans.SetLocation(controller->GetLocationUnderCursor());
		m_CurrentDisplayObject = world->SpawnActor<AConstructableObject>(m_CurrentSelectedClass, spawnTrans);
		m_CurrentDisplayObject->ToggleCollision(false);
	}

	if (m_CurrentDisplayObject != NULL)
	{
		m_CurrentDisplayObject->SetActorLocation(controller->GetLocationUnderCursor());
	}

	if (controller->IsLeftBtnPressed())
	{
		if (m_CurrentSelectedClass->IsChildOf(AFloorBlock::StaticClass()))
		{
			ABaseBlock* blocksUnder = Cast<ABaseBlock>(controller->GetObjectUnderCursor());
			if (blocksUnder != NULL)
			{
				blocksUnder->ChangeDisplayMode(ABaseBlock::Selected);
				m_CurrentSelectedBaseBlocks.AddUnique(blocksUnder);
			}
		}
	}
	else if (controller->WasLeftBtnReleased())
	{
		SpawnSelectedObject();
	}
}

void FInnManager::AddSelectedBaseBlock(ABaseBlock* block)
{
	m_CurrentSelectedBaseBlocks.AddUnique(block);
}

void FInnManager::LoadGame(FString slotName)
{

}

ATable* FInnManager::FindTable(FTableSearchRequest request)
{
	TArray<ATable*> foundTables = request.ApplyOn(m_CurrentTables);
	if (foundTables.Num() > 0)
	{
		return foundTables[0];
	}
	else
	{
		return nullptr;
	}
}

void FInnManager::AddTableData(FTableData tableData)
{
	if (m_CurrentInnSaveData == nullptr)
	{
		m_CurrentInnSaveData = NewObject<UInnData>();
	}

	int index = m_CurrentInnSaveData->Tables.Num();
	tableData.TableIndex = index;
	m_CurrentInnSaveData->Tables.Add(tableData);
}

void FInnManager::ClearCurrentTableData()
{
	m_CurrentInnSaveData->Tables.Empty();
}

UMaterial* FInnManager::LoadFloorBlockAssetMat(EFloorBlockMaterial blockMat)
{
	FString assetDir = m_GameManager->FloorBlockAssetDir;
	FString assetPath = assetDir;

	switch (blockMat)
	{
	case EFloorBlockMaterial::Mud:
		assetPath += "/Mud.Mud";
		break;
	case EFloorBlockMaterial::Plank:
		assetPath += "/Plank.Plank";
		break;
	case EFloorBlockMaterial::Granite:
		assetPath += "/Granite.Granite";
		break;
	case EFloorBlockMaterial::Bamboo:
		assetPath += "/Bamboo.Bamboo";
		break;
	case EFloorBlockMaterial::Brick:
		assetPath += "/Brick.Brick";
		break;
	case EFloorBlockMaterial::GoldenBrick:
		assetPath += "/GoldenBrick.GoldenBrick";
		break;
	case EFloorBlockMaterial::Jade:
		assetPath += "/Jade.Jade";
		break;
	default:
		break;
	}

	UMaterial* loadedMat = Cast<UMaterial>(StaticLoadObject(UMaterial::StaticClass(), NULL, *assetPath));

	return loadedMat;
}

void FInnManager::EnterConstructMode()
{
	m_CurrentMode = EInnManagerMode::Construct;

	for (int i = 0; i < m_BaseBlocks.Num(); ++i)
	{
		if (ABaseBlock* block = m_BaseBlocks[i])
		{
			block->ChangeDisplayMode(ABaseBlock::EBaseBlockDisplayMode::Normal);
		}
	}
}

void FInnManager::ExitConstructMode()
{
	m_CurrentMode = EInnManagerMode::Normal;

	for (int i = 0; i < m_BaseBlocks.Num(); ++i)
	{
		if (ABaseBlock* block = m_BaseBlocks[i])
		{
			block->ChangeDisplayMode(ABaseBlock::EBaseBlockDisplayMode::Transparent);
		}
	}
}

void FInnManager::SpawnFloorBlock()
{
	for (int i = 0;i<m_CurrentSelectedBaseBlocks.Num();++i)
	{
		UWorld* world = m_GameManager->GetAssociatedWorld();
		if (world)
		{
			//TODO: Use AFActorSpawnParameters
			//FActorSpawnParameters params;
			FTransform spawnTrans = m_CurrentSelectedBaseBlocks[i]->GetTransform();
			spawnTrans.AddToTranslation(FVector(0.f, 0.f, 3.f));//use majic number for now
			AFloorBlock* spawnedCustomer = world->SpawnActor<AFloorBlock>(m_FloorBlockClass, spawnTrans);
			//m_FloorBlockClass.Add(spawnedCustomer);
		}
	}

	//Clear out selected blocks
	m_CurrentSelectedBaseBlocks.Empty();
}

void FInnManager::SpawnSelectedObject()
{
	for (int i = 0; i < m_CurrentSelectedBaseBlocks.Num(); ++i)
	{
		UWorld* world = m_GameManager->GetAssociatedWorld();
		if (world)
		{
			//TODO: Use AFActorSpawnParameters
			//FActorSpawnParameters params;
			FTransform spawnTrans = m_CurrentSelectedBaseBlocks[i]->GetTransform();
			m_CurrentSelectedBaseBlocks[i]->ChangeDisplayMode(ABaseBlock::Normal);
			AConstructableObject* spawnedObject = world->SpawnActor<AConstructableObject>(m_CurrentSelectedClass, spawnTrans);
			//m_FloorBlockClass.Add(spawnedCustomer);
		}
	}

	//Clear out selected blocks
	m_CurrentSelectedBaseBlocks.Empty();
}

void FInnManager::SetSelectedClass(TSubclassOf<AConstructableObject> objectClass)
{
	m_CurrentSelectedClass = objectClass;

	//Spawn display actor under cursor

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Character/Customer/CustomerData.h"
#include "Manager/InnData.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameManager::AGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGameManager::BeginPlay()
{
	InitializeManager();
	Super::BeginPlay();
}

// Called every frame
void AGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_InnManager.Tick();
}

UWorld* AGameManager::GetAssociatedWorld() const
{
	return GetWorld();
}

void AGameManager::InitializeManager()
{
	m_CustomerManager.InitializeManager(this);
	m_InnManager.InitializeManager(this);
}

AGameManager* AGameManager::GetGameManager(UWorld* world)
{
	for (TActorIterator<AGameManager> It(world, AGameManager::StaticClass()); It; ++It)
	{
		AGameManager* gameManager = *It;
		return gameManager;
	}

	return nullptr;
}

void AGameManager::ChangeInnManagerMode(EInnManagerMode mode)
{
	switch (mode)
	{
	case EInnManagerMode::Normal:
		m_InnManager.ExitConstructMode();
		break;
	case EInnManagerMode::Construct:
		m_InnManager.EnterConstructMode();
		break;
	case EInnManagerMode::Decorate:
		break;
	default:
		break;
	}
}

void AGameManager::SetCurrentSelectedClass(TSubclassOf<AConstructableObject> objectClass)
{
	m_InnManager.SetSelectedClass(objectClass);
}

TSubclassOf<AConstructableObject> AGameManager::LoadObjectClassViaTypeAndLevel(EConstructableObjectType objectType, int level)
{
	return m_InnManager.LoadClassViaTypeAndLevel(objectType, level);
}

void AGameManager::SetCurrentLayer(int layerNumber)
{
	m_InnManager.SetCurrentLayer(layerNumber);
}

void AGameManager::SpawnFromSavedData()
{
	m_InnManager.SpawnFromSavedData();
}

//------------------------------------------------------------------------------
//Test Functions
void AGameManager::Test_SpawnCustomer(const FVector& refPos, const FRotator& refRot)
{
	m_CustomerManager.SpawnCustomerAt(refPos, refRot);
}

void AGameManager::Test_SpawnTables()
{
	m_InnManager.SpawnTables();
}

void AGameManager::Test_SpawnCustomerGroup(const FVector& refPos, const FRotator& refRot, const FCustomerGroupFormation& formation)
{
	m_CustomerManager.SpawnCustomerGroupAt(refPos, refRot, formation);
}

void AGameManager::Test_ClearCustomers()
{
	m_CustomerManager.ClearExistingCustomers();
}

void AGameManager::Test_AddTable(FTableData tableData)
{

}

void AGameManager::Test_ClearTable()
{

}

void AGameManager::Test_SaveGame(FString slotName)
{
	m_InnManager.SaveGame(slotName);
}

UMaterial* AGameManager::Test_LoadFloorBlockMat(EFloorBlockMaterial mat)
{
	return nullptr;
}

void AGameManager::Test_OrganizeBaseBlocks()
{
	m_InnManager.OrganizeBaseBlocks();
}

void AGameManager::Test_ResetSaveData()
{
	UInnData* newInnData = NewObject<UInnData>();
	UGameplayStatics::SaveGameToSlot(newInnData, "Slot1", 0);
	m_InnManager.ResetSaveData();
}
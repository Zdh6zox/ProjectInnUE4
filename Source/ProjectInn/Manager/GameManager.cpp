// Fill out your copyright notice in the Description page of Project Settings.


#include "GameManager.h"
#include "Character/Customer/CustomerData.h"
#include "EngineUtils.h"

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
	m_InnManager.AddTableData(tableData);
}

void AGameManager::Test_ClearTable()
{
	m_InnManager.ClearCurrentTableData();
}

void AGameManager::Test_SaveGame(FString slotName)
{
	m_InnManager.SaveGame(slotName);
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

UMaterial* AGameManager::Test_LoadFloorBlockMat(EFloorBlockMaterial mat)
{
	return m_InnManager.LoadFloorBlockAssetMat(mat);
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

void AGameManager::SetSelectedClass(TSubclassOf<AConstructableObject> selectedClass)
{
	m_InnManager.SetSelectedClass(selectedClass);
}

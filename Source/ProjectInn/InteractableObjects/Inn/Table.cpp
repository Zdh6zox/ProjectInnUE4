// Fill out your copyright notice in the Description page of Project Settings.


#include "Table.h"
#include "TableData.h"
#include "Character/Customer/CustomerGroup.h"
#include "ProjectInnPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectInn.h"



// Sets default values
ATable::ATable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATable::BeginPlay()
{
	Super::BeginPlay();

	AProjectInnPlayerController* innPlayerController = Cast<AProjectInnPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (innPlayerController != nullptr)
	{
		FScriptDelegate focusedDelegate;
		focusedDelegate.BindUFunction(this, "OnMouseFocused");
		innPlayerController->MouseFocusedOneParamDel.Add(focusedDelegate);

		FScriptDelegate clickedDelegate;
		clickedDelegate.BindUFunction(this, "OnMouseLeftBtnClicked");
		innPlayerController->MouseLeftBtnClickedOneParamDel.Add(clickedDelegate);


	}
}

// Called every frame
void ATable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATable::InitializeTable(FTableData tableDataBase)
{
	FTableRuntimeData* runtimeData = new FTableRuntimeData(tableDataBase);

	m_RuntimeData = MakeShareable(runtimeData);
}



void ATable::OccupiedBy(TWeakPtr<FCustomerGroup> group)
{
	m_RuntimeData->SetOccupiedGroup(group);
}

void ATable::OnMouseFocused_Implementation(AActor* focusedActor)
{
	if (focusedActor == this)
	{
		OnMouseFocusedOnThis_BP();
	}
}

void ATable::OnMouseLeftBtnClicked_Implementation(AActor* focusedActor)
{
	if (focusedActor == this)
	{
		OnMouseLeftBtnClickedOnThis_BP();
	}
}

void ATable::OnMouseFocusLeft_Implementation()
{
	OnMouseFocusLeft_BP();
}

bool ATable::GetIsAvailable(TWeakPtr<FCustomerGroup> group)
{
	if (group == m_RuntimeData->GetOccupiedGroup())
	{
		return true;
	}

	return m_RuntimeData->GetIsOccupied();
}

FTableData ATable::Test_CreateTableData()
{
	FTableData newTableData;
	newTableData.TableTransform = GetActorTransform();
	return newTableData;
}

void ATable::ToggleCollision(bool enable)
{
	ToggleCollision_BP(enable);
}
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Manager/CustomerManager.h"
#include "Manager/InnManager.h"
#include "Manager/RecipeManager.h"
#include "Character/Customer/Customer.h"
#include "Character/Customer/CustomerGroup.h"
#include "Engine/DataTable.h" 
#include "InteractableObjects/Inn/TableData.h"
#include "InteractableObjects/Inn/Table.h"
#include "GameManager.generated.h"


UCLASS()
class PROJECTINN_API AGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UWorld* GetAssociatedWorld() const;

	UFUNCTION(BlueprintCallable)
		void Test_SpawnCustomer(const FVector& refPos, const FRotator& refRot);

	UFUNCTION(BlueprintCallable)
		void Test_SpawnCustomerGroup(const FVector& refPos, const FRotator& refRot, const FCustomerGroupFormation& formation);

	UFUNCTION(BlueprintCallable)
		void Test_ClearCustomers();

	UFUNCTION(BlueprintCallable)
		void Test_SpawnTables();

	UFUNCTION(BlueprintCallable)
		void Test_AddTable(FTableData tableData);

	UFUNCTION(BlueprintCallable)
		void Test_ClearTable();

	UFUNCTION(BlueprintCallable)
		void Test_SaveGame(FString slotName);

	UPROPERTY(VisibleAnywhere, Transient)
		TArray<ACustomer*> AllCustomers;

	UPROPERTY(EditAnywhere, category = "Customer Manager")
		TSubclassOf<ACustomer> CustomerTemplate;

	UPROPERTY(EditAnywhere, category = "Customer Manager")
		UDataTable* CustomerDataTable;

	UPROPERTY(EditAnywhere, category = "Inn Manager")
		TSubclassOf<ATable> TableTemplate;

	static AGameManager* GetGameManager(UWorld* world);

	FInnManager GetInnManager() { return m_InnManager; }
	FCustomerManager GetCustomerManager() { return m_CustomerManager; }
	FRecipeManager GetRecipeManager() { return m_RecipeManager; }

private:
	void InitializeManager();
	FCustomerManager m_CustomerManager;
	FInnManager m_InnManager;
	FRecipeManager m_RecipeManager;
};

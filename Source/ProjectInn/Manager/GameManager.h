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
#include "InteractableObjects/Inn/FloorBlock.h"
#include "SharedEnumTypes.h"
#include "Materials/Material.h"
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

	UFUNCTION(BlueprintCallable,category = "Test Function")
		void Test_SpawnCustomer(const FVector& refPos, const FRotator& refRot);

	UFUNCTION(BlueprintCallable, category = "Test Function")
		void Test_SpawnCustomerGroup(const FVector& refPos, const FRotator& refRot, const FCustomerGroupFormation& formation);

	UFUNCTION(BlueprintCallable, category = "Test Function")
		void Test_ClearCustomers();

	UFUNCTION(BlueprintCallable, category = "Test Function")
		void Test_SpawnTables();

	UFUNCTION(BlueprintCallable, category = "Test Function")
		void Test_AddTable(FTableData tableData);

	UFUNCTION(BlueprintCallable, category = "Test Function")
		void Test_ClearTable();

	UFUNCTION(BlueprintCallable, category = "Test Function")
		void Test_SaveGame(FString slotName);

	UFUNCTION(BlueprintCallable, category = "Test Function")
		UMaterial* Test_LoadFloorBlockMat(EFloorBlockMaterial mat);

	UFUNCTION(BlueprintCallable, category = "Test Function")
		void Test_OrganizeBaseBlocks();

	UFUNCTION(BlueprintCallable, category = "Test Function")
		void Test_ResetSaveData();

	UFUNCTION(BlueprintCallable, category = "Inn Manager")
		void ChangeInnManagerMode(EInnManagerMode mode);

	UFUNCTION(BlueprintCallable, category = "Inn Manager")
		void SetCurrentSelectedClass(TSubclassOf<AConstructableObject> objectClass);

	UFUNCTION(BlueprintCallable, category = "Inn Manager")
		TSubclassOf<AConstructableObject> LoadObjectClassViaTypeAndLevel(EConstructableObjectType objectType, int level);

	UFUNCTION(BlueprintCallable, category = "Inn Manager")
		void SetCurrentLayer(int layerNumber);

	UFUNCTION(BlueprintCallable, category = "Inn Manager")
		void SpawnFromSavedData();

	UPROPERTY(VisibleAnywhere, Transient)
		TArray<ACustomer*> AllCustomers;

	UPROPERTY(EditAnywhere, category = "Customer Manager")
		TSubclassOf<ACustomer> CustomerTemplate;

	UPROPERTY(EditAnywhere, category = "Customer Manager")
		UDataTable* CustomerDataTable;

	UPROPERTY(EditAnywhere, category = "Inn Manager")
		TSubclassOf<ATable> TableTemplate;

	UPROPERTY(EditAnywhere, category = "Floor Block Assets")
		FString FloorBlockAssetDir;

	UPROPERTY(EditAnywhere, category = "Floor Block Assets")
		TSubclassOf<AFloorBlock> FloorBlockTemplate;

	static AGameManager* GetGameManager(UWorld* world);

	FInnManager& GetInnManager() { return m_InnManager; }
	FCustomerManager& GetCustomerManager() { return m_CustomerManager; }
	FRecipeManager& GetRecipeManager() { return m_RecipeManager; }

private:
	void InitializeManager();
	FCustomerManager m_CustomerManager;
	FInnManager m_InnManager;
	FRecipeManager m_RecipeManager;
};

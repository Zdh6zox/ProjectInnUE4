// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TableData.h"
#include "ConstructableObject.h"
#include "Table.generated.h"

class FTableRuntimeData;
class FCustomerGroup;

UCLASS()
class PROJECTINN_API ATable : public AConstructableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void InitializeTable(FTableData tableDataBase);

	void OccupiedBy(TWeakPtr<FCustomerGroup> group);

	bool GetIsAvailable(TWeakPtr<FCustomerGroup> group);

	UFUNCTION(BlueprintCallable)
        FTableData Test_CreateTableData();

	virtual void OnMouseLeftBtnClicked_Implementation(AActor* focusedActor) override;

	virtual void OnMouseFocused_Implementation(AActor* focusedActor) override;

	virtual void OnMouseFocusLeft_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent)
		void OnMouseLeftBtnClickedOnThis_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void OnMouseFocusedOnThis_BP();

	UFUNCTION(BlueprintImplementableEvent)
		void OnMouseFocusLeft_BP();

private:
	TSharedPtr<FTableRuntimeData> m_RuntimeData;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

class AGameManager;
class ACustomer;
class FCustomerGroup;
struct FCustomerData;
struct FCustomerGroupFormation;
/**
 * 
 */
class PROJECTINN_API FCustomerManager
{
public:
	void InitializeManager(AGameManager* gm);
	void SpawnCustomerAt(FVector refPos, FRotator refRot);
	void SpawnCustomerGroupAt(FVector refPos, FRotator refRot, FCustomerGroupFormation groupFormation);
	void FindCustomerData(TArray<FCustomerData>& foundCustomerData);
	void ClearExistingCustomers();

	TWeakPtr<FCustomerGroup> FindRespondingGroup(ACustomer* customer) const;
private:
	TWeakObjectPtr<AGameManager> m_GameManager;
	TSubclassOf<ACustomer> m_CustomerClass;
	TArray<ACustomer*> m_SpawnedCustomers;
	TArray<TSharedPtr<FCustomerGroup>> m_SpawnedGroups;
	UDataTable* m_CustomerDataTable;
};

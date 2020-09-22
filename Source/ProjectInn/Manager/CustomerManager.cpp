// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerManager.h"
#include "GameManager.h"
#include "ProjectInn.h"
#include "Character/Customer/Customer.h"
#include "Character/Customer/CustomerController.h"
#include "Character/Customer/CustomerGroup.h"
#include "Character/Customer/CustomerData.h"
#include "Engine/DataTable.h"
#include "UObject/ConstructorHelpers.h"

void FCustomerManager::InitializeManager(AGameManager* gm)
{
	m_GameManager = MakeWeakObjectPtr(gm);

	m_CustomerClass = gm->CustomerTemplate;
	if (m_CustomerClass == nullptr)
	{
		UE_LOG(LogProjectInn, Error, TEXT("miss customer template setup in GameManager"));
	}

	m_CustomerDataTable = gm->CustomerDataTable;
	if (m_CustomerDataTable == nullptr)
	{
		UE_LOG(LogProjectInn, Error, TEXT("miss customer data table setup in GameManager"));
	}

	//Clear out old data
	m_SpawnedCustomers.Empty();
	m_SpawnedGroups.Empty();
}

void FCustomerManager::SpawnCustomerAt(FVector refPos, FRotator refRot)
{
	if (!m_GameManager.IsValid())
	{
		return;
	}

	UWorld* world = m_GameManager->GetAssociatedWorld();
	if (world)
	{
		//TODO: Use AFActorSpawnParameters
		//FActorSpawnParameters params;
		ACustomer* spawnedCustomer = world->SpawnActor<ACustomer>(m_CustomerClass, refPos, refRot);
		m_SpawnedCustomers.Add(spawnedCustomer);
	}
}

void FCustomerManager::SpawnCustomerGroupAt(FVector refPos, FRotator refRot, FCustomerGroupFormation groupFormation)
{
	if (!m_GameManager.IsValid())
	{
		return;
	}

	if (groupFormation.GetFormationMemberNumber() <= 0)
	{
		return;
	}

	UWorld* world = m_GameManager->GetAssociatedWorld();
	if (world)
	{
		TArray<ACustomer*> spawnedCustomerList;
		//TODO: Use AFActorSpawnParameters
		//FActorSpawnParameters params;
		ACustomer* spawnedCustomer = world->SpawnActor<ACustomer>(m_CustomerClass, refPos, refRot);
		spawnedCustomerList.Add(spawnedCustomer);

		for (int i = 1; i < groupFormation.GetFormationMemberNumber(); ++i)
		{
			ACustomer* spawnedMember = world->SpawnActor<ACustomer>(m_CustomerClass, refPos, refRot);
			spawnedCustomerList.Add(spawnedMember);
		}

		m_SpawnedCustomers.Append(spawnedCustomerList);

		FCustomerGroup* newGroup = new FCustomerGroup(spawnedCustomerList, spawnedCustomer, groupFormation);
		m_SpawnedGroups.Add(MakeShareable(newGroup));
	}

}

TWeakPtr<FCustomerGroup> FCustomerManager::FindRespondingGroup(ACustomer* customer) const
{
	for (int i = 0; i < m_SpawnedGroups.Num(); ++i)
	{
		TSharedPtr<FCustomerGroup> group = m_SpawnedGroups[i];
		if (group->IsInsideGroup(customer))
		{
			return group;
		}
	}

	return nullptr;
}

void FCustomerManager::ClearExistingCustomers()
{
	m_SpawnedGroups.Empty();
	for (int i = 0; i < m_SpawnedCustomers.Num(); ++i)
	{
		m_SpawnedCustomers[i]->Destroy();
	}
}

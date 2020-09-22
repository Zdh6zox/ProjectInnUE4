// Fill out your copyright notice in the Description page of Project Settings.


#include "TableSearchRequest.h"
#include "Character/Customer/Customer.h"
#include "InteractableObjects/Inn/Table.h"
#include "Manager/GameManager.h"

FTableSearchRequest::FTableSearchRequest(ACustomer* requester)
{
	m_Requester = requester;
}

FTableSearchRequest FTableSearchRequest::CreateTableSearchRequest(ACustomer* requester)
{
	//Temp : just return random table that not occupied, so no special operation here
	FTableSearchRequest* request = new FTableSearchRequest(requester);
	return *request;
}

TArray<ATable*> FTableSearchRequest::ApplyOn(const TArray<ATable*>& tables)
{
	//Temp : just return random table that not occupied
	TArray<ATable*> foundTables;
	TArray<ATable*> availableTables;
	
	TWeakPtr<FCustomerGroup> group = m_Requester->GetBelongingGroup();

	for (int i = 0; i < tables.Num(); ++i)
	{
		ATable* table = tables[i];

		if (table != nullptr && table->GetIsAvailable(group))
		{
			availableTables.Add(table);
		}
	}

	if (availableTables.Num())
	{
		foundTables.Add(availableTables[0]);
	}

	return foundTables;
}
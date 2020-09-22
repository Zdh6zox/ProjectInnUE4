// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerGroup.h"
#include "Customer.h"
#include "ProjectInn.h"


FCustomerGroup::FCustomerGroup(TArray<ACustomer *> members, ACustomer* leader, FCustomerGroupFormation groupFormation)
{
	m_GroupLeader = leader;
	m_GroupMembers = members;
	m_GroupFormation = groupFormation;
}

bool FCustomerGroup::IsInsideGroup(ACustomer* customer) const
{
	return m_GroupMembers.Contains(customer);
}

void FCustomerGroup::AddIntoGroup(ACustomer* customer)
{
	if (!m_GroupMembers.Contains(customer))
	{
		m_GroupMembers.Add(customer);
	}
	else
	{
		UE_LOG(LogProjectInn, Error, TEXT("Trying to add same customer %s into one group %d"), *customer->GetName(), m_GroupUniqueID);
	}
}

void FCustomerGroup::RemoveFromGroup(ACustomer* customer)
{
	if (m_GroupMembers.Contains(customer))
	{
		m_GroupMembers.Remove(customer);
	}
	else
	{
		UE_LOG(LogProjectInn, Error, TEXT("Trying to remove customer %s that is not in group %d"), *customer->GetName(), m_GroupUniqueID);
	}
}
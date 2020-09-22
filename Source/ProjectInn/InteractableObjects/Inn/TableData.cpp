// Fill out your copyright notice in the Description page of Project Settings.


#include "TableData.h"
#include "Character/Customer/CustomerGroup.h"

FTableRuntimeData::FTableRuntimeData(TSharedPtr<FTableData> tableData)
{
	m_TableData = tableData;
}

void FTableRuntimeData::SetOccupiedGroup(TWeakPtr<FCustomerGroup> customerGroup)
{
	m_OccupiedGroup = customerGroup;
}

TWeakPtr<FCustomerGroup> FTableRuntimeData::GetOccupiedGroup()
{
	return m_OccupiedGroup;
}

bool FTableRuntimeData::GetIsOccupied() const
{
	return m_OccupiedGroup.IsValid();
}
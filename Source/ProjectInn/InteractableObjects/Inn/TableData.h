// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TableData.generated.h"
/**
 * 
 */
class FCustomerGroup;

USTRUCT(BlueprintType)
struct PROJECTINN_API FTableData
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere)
		int TableIndex;

	UPROPERTY(EditAnywhere)
		FTransform TableTransform;
};

class PROJECTINN_API FTableRuntimeData
{
public:
	FTableRuntimeData(TSharedPtr<FTableData> tableData);

	void SetOccupiedGroup(TWeakPtr<FCustomerGroup> customerGroup);
	bool GetIsOccupied() const;
	TWeakPtr<FCustomerGroup> GetOccupiedGroup();

private:
	TSharedPtr<FTableData> m_TableData;
	TWeakPtr<FCustomerGroup> m_OccupiedGroup;
};
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomerGroup.generated.h"
/**
 * 
 */

class ACustomer;

USTRUCT(BlueprintType)
struct PROJECTINN_API FCustomerGroupFormationEntry
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		FVector LocalPosition = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
		FRotator LocalRotation = FRotator::ZeroRotator;
};

USTRUCT(BlueprintType)
struct PROJECTINN_API FCustomerGroupFormation
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere)
		TArray<FCustomerGroupFormationEntry> EntryList;

	int GetFormationMemberNumber() { return EntryList.Num(); }
};

class PROJECTINN_API FCustomerGroup
{
public:
	FCustomerGroup(TArray<ACustomer*> members, ACustomer* leader, FCustomerGroupFormation groupFormation);

	ACustomer* GetGroupLeader() const { return m_GroupLeader; }
	void SetGroupLeader(ACustomer* customer) { m_GroupLeader = customer; }

	bool IsInsideGroup(ACustomer* customer) const;
	void RemoveFromGroup(ACustomer* customer);
	void AddIntoGroup(ACustomer* customer);

private:
	int m_GroupUniqueID;
	ACustomer* m_GroupLeader;
	TArray<ACustomer*> m_GroupMembers;
	FCustomerGroupFormation m_GroupFormation;
};

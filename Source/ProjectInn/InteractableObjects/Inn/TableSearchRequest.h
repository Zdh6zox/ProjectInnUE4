// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 
 */
class ACustomer;
class ATable;

class PROJECTINN_API FTableSearchRequest
{
public:
	FTableSearchRequest(ACustomer* requester);
	static FTableSearchRequest CreateTableSearchRequest(ACustomer* requester);
	TArray<ATable*> ApplyOn(const TArray<ATable*>& tables);

private:
	ACustomer* m_Requester;
};

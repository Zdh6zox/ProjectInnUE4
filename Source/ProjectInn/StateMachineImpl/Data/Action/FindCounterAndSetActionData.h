// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Action/ActionDataBase.h"
#include "FindCounterAndSetActionData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINN_API UFindCounterAndSetActionData : public UActionDataBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		FName CounterKey;

	virtual FActionBase* CreateAction() override;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Action/ActionDataBase.h"
#include "MoveToLocationActionData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINN_API UMoveToLocationActionData : public UActionDataBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere)
		FName LocationKey;

	UPROPERTY(EditAnywhere)
		bool ObjectAsDest;

	UPROPERTY(EditAnywhere)
		float IsReachThreshold;

	virtual FActionBase* CreateAction() override;
};

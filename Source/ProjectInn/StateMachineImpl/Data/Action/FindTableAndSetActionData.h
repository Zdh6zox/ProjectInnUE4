// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Action/ActionDataBase.h"
#include "FindTableAndSetActionData.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTINN_API UFindTableAndSetActionData : public UActionDataBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		FName TableKey;

	virtual FActionBase* CreateAction() override;

};

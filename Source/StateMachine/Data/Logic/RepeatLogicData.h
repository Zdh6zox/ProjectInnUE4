// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Logic/LogicDataBase.h"
#include "Data/Action/ActionDataBase.h"
#include "RepeatLogicData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STATEMACHINEMODULE_API URepeatLogicData : public ULogicDataBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int RepeatTimes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Instanced)
		UActionDataBase* Action;

	virtual FLogicBase* ConstructLogic() override;
};

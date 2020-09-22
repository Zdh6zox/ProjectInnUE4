// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/Logic/LogicDataBase.h"
#include "Data/Condition/ExpressionData.h"
#include "Data/Action/ActionDataBase.h"
#include "IfElseLogicData.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class STATEMACHINEMODULE_API UIfElseLogicData : public ULogicDataBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FExpressionData Expression;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		UActionDataBase* PositiveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
		UActionDataBase* NegativeAction;

	virtual FLogicBase* ConstructLogic() override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/Object.h"
#include "EdGraph/EdGraphPin.h"
#include "StateMachineEditorTypes.generated.h"

/**
 * 
 */

namespace EStateSubNode
{
	enum Type {
		Logic,
		EnterAction,
		ExitAction
	};
}

UCLASS()
class UStateMachineEditorTypes : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	static const FName PinCategory_ActionNode;
	static const FName PinCategory_StateNode;
	static const FName PinCategory_LogicNode;
};

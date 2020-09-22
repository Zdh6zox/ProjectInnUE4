// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "SMTransitionGraph.generated.h"


class UEdGraphPin;

/** Delegate fired when a pin's default value is changed */
DECLARE_MULTICAST_DELEGATE_OneParam(FOnPinDefaultValueChanged, UEdGraphPin* /*InPinThatChanged*/)
/**
 * 
 */
UCLASS()
class STATEMACHINEEDITORMODULE_API USMTransitionGraph : public UEdGraph
{
	GENERATED_UCLASS_BODY()
	
	/** Delegate fired when a pin's default value is changed */
	FOnPinDefaultValueChanged OnPinDefaultValueChanged;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputReceivableObject.generated.h"
/**
 * 
 */
UINTERFACE(BlueprintType)
class PROJECTINN_API UInputReceivableObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class PROJECTINN_API IInputReceivableObject
{
	GENERATED_IINTERFACE_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseLeftBtnClicked(AActor* focusedActor);

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseFocused(AActor* focusedActor);

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseFocusLeft();
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ConstructableObject.h"
#include "Counter.generated.h"

UCLASS()
class PROJECTINN_API ACounter : public AConstructableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACounter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnMouseLeftBtnClicked_Implementation(AActor* focusedActor) override;

	virtual void OnMouseFocused_Implementation(AActor* focusedActor) override;

	virtual void OnMouseFocusLeft_Implementation() override;
};

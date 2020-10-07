// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputReceivableObject.h"
#include "Data/ConstructableObjectData.h"
#include "ConstructableObject.generated.h"

UCLASS()
class PROJECTINN_API AConstructableObject : public AActor, public IInputReceivableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AConstructableObject();

	UPROPERTY(EditAnywhere)
	FConstructableObjectData ObjectData;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseLeftBtnClicked(AActor* focusedActor);
	void OnMouseLeftBtnClicked_Implementation(AActor* focusedActor) override;

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseFocused(AActor* focusedActor);
	void OnMouseFocused_Implementation(AActor* focusedActor) override;

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseFocusLeft();
	void OnMouseFocusLeft_Implementation() override;

	UFUNCTION(BlueprintNativeEvent)
		bool CanReceiveInput();
	bool CanReceiveInput_Implementation() override;

	virtual void ToggleCollision(bool enable) {}
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InputReceivableObject.h"
#include "BaseBlock.generated.h"


class UStaticMeshComponent;
UCLASS()
class PROJECTINN_API ABaseBlock : public AActor, public IInputReceivableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseBlock();

	enum EBaseBlockDisplayMode
	{
		Transparent,
		Normal,
		Error,
		Selected
	};

	UPROPERTY(EditAnywhere)
		int BlockIndex;

	EBaseBlockDisplayMode CurrentDisplayMode = EBaseBlockDisplayMode::Transparent;

	UPROPERTY(EditAnywhere)
		FLinearColor NormalColor;

	UPROPERTY(EditAnywhere)
		FLinearColor ErrorColor;

	UPROPERTY(EditAnywhere)
		FLinearColor SelectedColor;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeDisplayMode(EBaseBlockDisplayMode displayMode);

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseLeftBtnClicked(AActor* focusedActor);
	void OnMouseLeftBtnClicked_Implementation(AActor* focusedActor) override;

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseFocused(AActor* focusedActor);
	void OnMouseFocused_Implementation(AActor* focusedActor) override;

	UFUNCTION(BlueprintNativeEvent)
		void OnMouseFocusLeft();
	void OnMouseFocusLeft_Implementation() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;
};
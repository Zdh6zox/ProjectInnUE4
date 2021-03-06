// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/BaseBlockData.h"
#include "InputReceivableObject.h"
#include "SharedEnumTypes.h"
#include "BaseBlock.generated.h"


class UStaticMeshComponent;
class AConstructableObject;

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
		Highlight,
		Selected
	};

	UPROPERTY(EditAnywhere)
	FBlockCoordinate BlockCoordinate;

	EBaseBlockDisplayMode CurrentDisplayMode = EBaseBlockDisplayMode::Transparent;

	UPROPERTY(EditAnywhere)
		FLinearColor NormalColor;

	UPROPERTY(EditAnywhere)
		FLinearColor ErrorColor;

	UPROPERTY(EditAnywhere)
		FLinearColor SelectedColor;

	UPROPERTY(EditAnywhere)
		FLinearColor HighlightColor;

	UPROPERTY()
		TArray<AConstructableObject*> ObjectsOnThisBlock;

	UPROPERTY(EditAnywhere, category = "Neighbour Blocks")
		ABaseBlock* LeftBlock;

	UPROPERTY(EditAnywhere, category = "Neighbour Blocks")
		ABaseBlock* RightBlock;

	UPROPERTY(EditAnywhere, category = "Neighbour Blocks")
		ABaseBlock* UpBlock;

	UPROPERTY(EditAnywhere, category = "Neighbour Blocks")
		ABaseBlock* DownBlock;

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

	UFUNCTION(BlueprintNativeEvent)
		bool CanReceiveInput();
	bool CanReceiveInput_Implementation() override;

	void SetSelected(bool isSelected);

	bool CanPlace(EConstructableObjectType objectType, int layer) const;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* StaticMesh;

	bool m_IsSelected = false;
};

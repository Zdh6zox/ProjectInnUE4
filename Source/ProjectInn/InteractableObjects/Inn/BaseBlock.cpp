// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBlock.h"
#include "Manager/GameManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ABaseBlock::ABaseBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
void ABaseBlock::BeginPlay()
{
	Super::BeginPlay();
	ChangeDisplayMode(ABaseBlock::Transparent);
}


// Called every frame
void ABaseBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBlock::OnMouseFocused_Implementation(AActor* focusedActor)
{

}

void ABaseBlock::OnMouseFocusLeft_Implementation()
{

}

void ABaseBlock::OnMouseLeftBtnClicked_Implementation(AActor* focusedActor)
{

}

void ABaseBlock::ChangeDisplayMode(EBaseBlockDisplayMode displayMode)
{
	CurrentDisplayMode = displayMode;

	UMaterialInstanceDynamic* dynamicMat = StaticMesh->CreateDynamicMaterialInstance(0);

	switch (CurrentDisplayMode)
	{
	case ABaseBlock::Transparent:
		dynamicMat->SetScalarParameterValue("Opacity", 0.f);
		break;
	case ABaseBlock::Normal:
		dynamicMat->SetScalarParameterValue("Opacity", 0.3f);
		dynamicMat->SetVectorParameterValue("Color", NormalColor);
		break;
	case ABaseBlock::Error:
		dynamicMat->SetScalarParameterValue("Opacity", 0.3f);
		dynamicMat->SetVectorParameterValue("Color", ErrorColor);
		break;
	case ABaseBlock::Selected:
		dynamicMat->SetScalarParameterValue("Opacity", 0.3f);
		dynamicMat->SetVectorParameterValue("Color", SelectedColor);
		break;
	default:
		break;
	}
}
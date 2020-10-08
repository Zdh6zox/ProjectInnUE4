// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseBlock.h"
#include "Manager/GameManager.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "ConstructableObject.h"
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
	m_IsSelected = false;
	ChangeDisplayMode(ABaseBlock::Transparent);
	ObjectsOnThisBlock.Empty();
}


// Called every frame
void ABaseBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseBlock::OnMouseFocused_Implementation(AActor* focusedActor)
{
	if (focusedActor == this)
	{
		if (!m_IsSelected)
		{
			ChangeDisplayMode(ABaseBlock::Highlight);
		}
	}
}

void ABaseBlock::OnMouseFocusLeft_Implementation()
{
	if (!m_IsSelected)
	{
		ChangeDisplayMode(ABaseBlock::Normal);
	}
}

void ABaseBlock::SetSelected(bool isSelected)
{
	m_IsSelected = isSelected;
}

void ABaseBlock::OnMouseLeftBtnClicked_Implementation(AActor* focusedActor)
{

}

bool ABaseBlock::CanReceiveInput_Implementation()
{
	return AGameManager::GetGameManager(GetWorld())->GetInnManager().GetInnManagerMode() == EInnManagerMode::Construct;
}

void ABaseBlock::ChangeDisplayMode(EBaseBlockDisplayMode displayMode)
{
	CurrentDisplayMode = displayMode;

	UMaterialInstanceDynamic* dynamicMat = StaticMesh->CreateDynamicMaterialInstance(0);

	m_IsSelected = false;

	switch (CurrentDisplayMode)
	{
	case ABaseBlock::Transparent:
		dynamicMat->SetScalarParameterValue("Opacity", 0.f);
		break;
	case ABaseBlock::Normal:
		dynamicMat->SetScalarParameterValue("Opacity", 0.1f);
		dynamicMat->SetVectorParameterValue("Color", NormalColor);
		break;
	case ABaseBlock::Highlight:
		dynamicMat->SetScalarParameterValue("Opacity", 0.3f);
		dynamicMat->SetVectorParameterValue("Color", HighlightColor);
		break;
	case ABaseBlock::Error:
		dynamicMat->SetScalarParameterValue("Opacity", 0.3f);
		dynamicMat->SetVectorParameterValue("Color", ErrorColor);
		break;
	case ABaseBlock::Selected:
		dynamicMat->SetScalarParameterValue("Opacity", 0.3f);
		dynamicMat->SetVectorParameterValue("Color", SelectedColor);
		m_IsSelected = true;
		break;
	default:
		break;
	}
}
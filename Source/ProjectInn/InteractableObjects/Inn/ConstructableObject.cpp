// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstructableObject.h"

// Sets default values
AConstructableObject::AConstructableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AConstructableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AConstructableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AConstructableObject::OnMouseFocused_Implementation(AActor* focusedActor)
{
	//if (focusedActor == this)
	//{
	//	OnMouseFocusedOnThis_BP();
	//}
}

void AConstructableObject::OnMouseLeftBtnClicked_Implementation(AActor* focusedActor)
{
	//if (focusedActor == this)
	//{
	//	OnMouseLeftBtnClickedOnThis_BP();
	//}
}

void AConstructableObject::OnMouseFocusLeft_Implementation()
{
	//OnMouseFocusLeft_BP();
}

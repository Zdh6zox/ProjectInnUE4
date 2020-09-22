// Fill out your copyright notice in the Description page of Project Settings.


#include "Customer.h"
#include "CustomerController.h"
#include "CustomerDataRuntime.h"
#include "CustomerGroup.h"
#include "Manager/GameManager.h"
#include "ProjectInnPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "StateMachineImpl/Action/MoveToLocationAction.h"
#include "ProjectInn.h"

ACustomer::ACustomer()
	:ANonPlayerCharacter()
{
	//ACustomerController* controller = NewObject<ACustomerController>(this, "Customer Controller");
	//controller->SetPawn(this);
	//Controller = controller;
	AIControllerClass = ACustomerController::StaticClass();


}

void ACustomer::BeginPlay()
{
	Super::BeginPlay();

	m_IsTicked = false;

	ACustomerController* customerController = Cast<ACustomerController>(GetController());
	if (customerController && InitBlackboardData)
	{
		customerController->UseBlackboard(InitBlackboardData, m_CachedBlackboardComponent);
	}

	AProjectInnPlayerController* innPlayerController = Cast<AProjectInnPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (innPlayerController != nullptr)
	{
		FScriptDelegate focusedDelegate;
		focusedDelegate.BindUFunction(this, "OnMouseFocused");
		innPlayerController->MouseFocusedOneParamDel.Add(focusedDelegate);

		FScriptDelegate clickedDelegate;
		clickedDelegate.BindUFunction(this, "OnMouseLeftBtnClicked");
		innPlayerController->MouseLeftBtnClickedOneParamDel.Add(clickedDelegate);
	}
}

void ACustomer::Tick(float DeltaSeconds)
{
	if (!m_IsTicked)
	{

		m_IsTicked = true;
	}

	Super::Tick(DeltaSeconds);
}

void ACustomer::TestMove()
{
	FMoveToLocationAction* moveToLoc = new FMoveToLocationAction("Test_Move", "1", 0.0f);
}

UBlackboardComponent* ACustomer::GetBlackboardComponent() const
{
	return m_CachedBlackboardComponent;
}

TWeakPtr<FCustomerGroup> ACustomer::GetBelongingGroup()
{
	AGameManager* gm = AGameManager::GetGameManager(GetWorld());
	return gm->GetCustomerManager().FindRespondingGroup(this);
}

void ACustomer::OnMouseFocused_Implementation(AActor* focusedActor)
{
	if (focusedActor == this)
	{
		OnMouseFocusedOnThis_BP();
	}
}

void ACustomer::OnMouseLeftBtnClicked_Implementation(AActor* focusedActor)
{
	if (focusedActor == this)
	{
		OnMouseLeftBtnClickedOnThis_BP();
	}
}

void ACustomer::OnMouseFocusLeft_Implementation()
{
	OnMouseFocusLeft_BP();
}
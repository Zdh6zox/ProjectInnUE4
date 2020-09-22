// Fill out your copyright notice in the Description page of Project Settings.


#include "FindTableAndSetAction.h"
#include "Character/Customer/Customer.h"
#include "InteractableObjects/Inn/TableSearchRequest.h"
#include "Manager/GameManager.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "ProjectInn.h"


FFindTableAndSetAction::FFindTableAndSetAction(FString actionName, FName keyToStore)
	:super(actionName)
{
	m_KeyToStore = keyToStore;
}

void FFindTableAndSetAction::Init(TWeakPtr<FActionExecutionContext> ctx)
{
	super::Init(ctx);
}

void FFindTableAndSetAction::Execute(TWeakPtr<FActionExecutionContext> ctx)
{
	super::Execute(ctx);

	UStateMachineComponent* owner = ctx.Pin()->ExecuterComponent;
	ACustomer* customer = Cast<ACustomer>(owner->GetOwner());
	UBlackboardComponent* bbComp = customer->FindComponentByClass<UBlackboardComponent>();
	if (bbComp == nullptr)
	{
		UE_LOG(LogProjectInnStateMachineImpl, Error, TEXT("Cannot find blackboard component on %s"), *customer->GetName());
		m_ExecuteState = EActionExecuteState::Failure;
		return;
	}

	FTableSearchRequest newRequest = FTableSearchRequest::CreateTableSearchRequest(customer);

	AGameManager* gameManager = AGameManager::GetGameManager(customer->GetWorld());

	ATable* foundTable = gameManager->GetInnManager().FindTable(newRequest);
	if (foundTable)
	{
		bbComp->SetValueAsObject(m_KeyToStore, foundTable);
		m_ExecuteState = EActionExecuteState::Success;
	}
	else
	{
		bbComp->SetValueAsObject(m_KeyToStore, nullptr);
		m_ExecuteState = EActionExecuteState::Failure;
	}
}
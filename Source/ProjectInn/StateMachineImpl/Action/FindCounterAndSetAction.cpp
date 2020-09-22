// Fill out your copyright notice in the Description page of Project Settings.


#include "FindCounterAndSetAction.h"
#include "Manager/GameManager.h"
#include "InteractableObjects/Inn/Counter.h"
#include "Character/Customer/Customer.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "Manager/InnManager.h"

FFindCounterAndSetAction::FFindCounterAndSetAction(FString actionName, FName keyToStore)
	:super(actionName)
{
	m_KeyToStore = keyToStore;
}

void FFindCounterAndSetAction::Init(TWeakPtr<FActionExecutionContext> ctx)
{
	super::Init(ctx);
}

void FFindCounterAndSetAction::Execute(TWeakPtr<FActionExecutionContext> ctx)
{
	super::Execute(ctx);

	UStateMachineComponent* owner = ctx.Pin()->ExecuterComponent;
	ACustomer* customer = Cast<ACustomer>(owner->GetOwner());
	if (customer != nullptr)
	{
		ACounter* counter = AGameManager::GetGameManager(customer->GetWorld())->GetInnManager().FindCounter();
		
		UBlackboardComponent* bbCom = customer->FindComponentByClass<UBlackboardComponent>();
		if (bbCom != nullptr)
		{
			bbCom->SetValueAsObject(m_KeyToStore, counter);
		}
	}
}

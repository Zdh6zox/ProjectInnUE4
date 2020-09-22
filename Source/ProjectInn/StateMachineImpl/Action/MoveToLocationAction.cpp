// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToLocationAction.h"
#include "StateMachineLog.h"
#include "Character/Customer/Customer.h"
#include "Character/Customer/CustomerController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"

FMoveToLocationAction::FMoveToLocationAction(FString actionName, FName locationKey, float isReachThreshold)
	:FActionBase(actionName)
{
	m_LocationKey = locationKey;
	m_IsReachThreshold = isReachThreshold;
}

FMoveToLocationAction::~FMoveToLocationAction()
{
}

void FMoveToLocationAction::Init(TWeakPtr<FActionExecutionContext> ctx)
{
	super::Init(ctx);
}

void FMoveToLocationAction::Execute(TWeakPtr<FActionExecutionContext> ctx)
{
	super::Execute(ctx);

	UStateMachineComponent* owner = ctx.Pin()->ExecuterComponent;
	ACustomer* customer = Cast<ACustomer>(owner->GetOwner());
	FString ownerName;
	customer->GetName(ownerName);
	UE_LOG(LogStateMachineAction, Log, TEXT("Move To Location %s"), *ownerName);

	ACustomerController* customerController = Cast<ACustomerController>(customer->GetController());
	if (customerController)
	{
		UBlackboardComponent* bbComp = customer->GetBlackboardComponent();
		if (bbComp != nullptr)
		{
			customerController->MoveToPosition(bbComp->GetValueAsVector(m_LocationKey));
			if (customerController->IsMovingTo(bbComp->GetValueAsVector(m_LocationKey)))
			{
				m_ExecuteState = EActionExecuteState::Running;
			}
		}
		else
		{
			m_ExecuteState = EActionExecuteState::Failure;
		}
	}
	else
	{
		m_ExecuteState = EActionExecuteState::Failure;
	}
}
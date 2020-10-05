// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToLocationAction.h"
#include "StateMachineLog.h"
#include "Character/Customer/Customer.h"
#include "Character/Customer/CustomerController.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Actor.h"

FMoveToLocationAction::FMoveToLocationAction(FString actionName, FName locationKey, float isReachThreshold, bool objectAsDest)
	:FActionBase(actionName)
{
	m_LocationKey = locationKey;
	m_IsReachThreshold = isReachThreshold;
	m_ObjectAsDest = objectAsDest;
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
	UE_LOG(LogStateMachineAction, Log, TEXT("%s Moving To Location"), *ownerName);

	FVector destination = FVector::ZeroVector;
	UBlackboardComponent* bbComp = customer->GetBlackboardComponent();
	if (bbComp != nullptr)
	{
		if (m_ObjectAsDest)
		{
			AActor* destinationActor = Cast<AActor>(bbComp->GetValueAsObject(m_LocationKey));
			if (destinationActor != nullptr)
			{
				destination = destinationActor->GetTransform().GetLocation();
			}
		}
		else
		{
			destination = bbComp->GetValueAsVector(m_LocationKey);
		}
	}

	ACustomerController* customerController = Cast<ACustomerController>(customer->GetController());
	if (customerController)
	{
		if (!customerController->IsMovingTo(destination))
		{
			customerController->MoveToPosition(destination);
		}

		if (customerController->IsMovingTo(destination))
		{
			m_ExecuteState = EActionExecuteState::Running;
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
// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineComponent.h"
#include "StateMachineLog.h"

#include "Logic/IfElseLogic.h"
#include "Condition/ConstCondition.h"
#include "Condition/Expression.h"

// Sets default values for this component's properties
UStateMachineComponent::UStateMachineComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStateMachineComponent::BeginPlay()
{

	Super::BeginPlay();

	InitialStateMachineFromData();

	if (m_ActiveState.IsValid())
	{
		m_ActiveState.Pin()->InitContext(this);
		m_ActiveState.Pin()->EnterState();
	}
	//// ...
	////Test
	//FState* testState = new FState("Test State");
	//FState* testState2 = new FState("Test State 2");
	//FTransition* trans = new FTransition("1 to 2");
	//FIfElseLogic* logic = new FIfElseLogic();
	//FLogicContext* logicCtx = new FLogicContext();
	//logicCtx->SetOwner(GetOwner());
	//logic->InitLogicContext(MakeShareable(logicCtx));
	//FConstCondition* alwaysTrueCon = new FConstCondition();
	//logic->SetCondition(MakeShareable(alwaysTrueCon));
	//TSharedPtr<FState> testState2Shared = MakeShareable(testState2);
	//trans->SetNextState(testState2Shared);
	//testState->AddTransition(MakeShareable(trans));
	//testState2->AddLogic(MakeShareable(logic));
	//m_ActiveState = MakeShareable(testState);
	//m_States.Add(m_ActiveState);
	//m_States.Add(testState2Shared);
}

void UStateMachineComponent::InitialStateMachineFromData()
{
	if (StateMachineData != nullptr)
	{
		TArray<TSharedPtr<FState>> states = StateMachineData->CreateStatesWithTransition();
		for (int i = 0; i < states.Num(); ++i)
		{
			m_States = states;
			if (i == 0)
			{
				m_ActiveState = m_States[0];
			}
		}
	}
}

void UStateMachineComponent::BeginDestroy()
{
	Super::BeginDestroy();

	m_States.Empty();
}

// Called every frame
void UStateMachineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!m_ActiveState.IsValid())
	{
		UE_LOG(LogStateMachine, Error, TEXT("Active State is null"));
		return;
	}


	for (int i = 0; i < m_ActiveState.Pin()->GetTransitions().Num(); ++i)
	{
		const TSharedPtr<FTransition>& transtion = m_ActiveState.Pin()->GetTransitions()[i];
		if (!transtion.IsValid())
		{
			UE_LOG(LogStateMachine, Error, TEXT("Transtion is null"));
			continue;
		}
		 
		FTransition* transPtr = transtion.Get();
		if (transPtr->IsValid(this))
		{
			TWeakPtr<FState> nextState = transPtr->GetNextState();
			if (nextState.IsValid())
			{
				m_ActiveState.Pin()->ExitState();
				m_ActiveState.Pin()->ResetContext();
				m_ActiveState = nextState;
				m_ActiveState.Pin()->InitContext(this);
				m_ActiveState.Pin()->EnterState();
				return;
			}
		}
	}

	m_ActiveState.Pin()->Update();
}
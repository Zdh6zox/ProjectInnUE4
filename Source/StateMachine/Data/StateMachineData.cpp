// Fill out your copyright notice in the Description page of Project Settings.


#include "StateMachineData.h"
#include "Data/State/StateData.h"
#include "Data/State/TransitionData.h"
#include "State/State.h"
#include "State/Transition.h"

TArray<TSharedPtr<FState>> UStateMachineData::CreateStatesWithTransition()
{
	TArray<TSharedPtr<FState>> createdStates;
	for (int i = 0; i < States.Num(); ++i)
	{
		UStateData* stateData = States[i];
		if (stateData == nullptr)
		{
			continue;
		}

		createdStates.Add(MakeShareable(stateData->CreateState()));
	}
	
	for (int i = 0; i < States.Num(); ++i)
	{
		UStateData* stateData = States[i];
		if (stateData == nullptr)
		{
			continue;
		}

		for (int j = 0; j < stateData->Transitions.Num(); ++j)
		{
			UTransitionData* transitionData = stateData->Transitions[j];
			if (transitionData == nullptr)
			{
				continue;
			}

			FTransition* trans = transitionData->CreateTransition();
			TSharedPtr<FState> nextState = FindStateViaName(createdStates, transitionData->NextStateName);
			if (nextState != nullptr)
			{
				trans->SetNextState(nextState);
			}

			TSharedPtr<FState> belongingState = FindStateViaName(createdStates, stateData->StateName);
			if (belongingState != nullptr)
			{
				belongingState->AddTransition(MakeShareable(trans));
			}
		}
	}
	
	return createdStates;
}

TSharedPtr<FState> UStateMachineData::FindStateViaName(const TArray<TSharedPtr<FState>> states, FString stateName)
{
	for (int i = 0; i < states.Num(); i++)
	{
		TSharedPtr<FState> state = states[i];
		if (state != nullptr && state->GetStateName() == stateName)
		{
			return state;
		}
	}

	return nullptr;
}

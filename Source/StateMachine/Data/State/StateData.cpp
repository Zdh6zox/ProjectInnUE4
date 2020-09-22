// Fill out your copyright notice in the Description page of Project Settings.


#include "StateData.h"
#include "TransitionData.h"
#include "State/State.h"
#include "State/Transition.h"
#include "Data/StateMachineData.h"
#include "Data/Logic/LogicDataBase.h"
#include "Data/Action/ActionDataBase.h"
#include "TransitionData.h"

FState* UStateData::CreateState()
{
	FState* newState = new FState(StateName);

	for (int i = 0; i < EnterActions.Num(); ++i)
	{
		UActionDataBase* actionData = EnterActions[i];
		if (actionData == nullptr)
		{
			continue;
		}
		newState->AddEnterAction(MakeShareable(actionData->CreateAction()));
	}

	for (int i = 0; i < UpdateLogics.Num(); ++i)
	{
		ULogicDataBase* logicData = UpdateLogics[i];
		if (logicData == nullptr)
		{
			continue;
		}
		newState->AddUpdateLogic(MakeShareable(logicData->ConstructLogic()));
	}

	for (int i = 0; i < ExitActions.Num(); ++i)
	{
		UActionDataBase* actionData = ExitActions[i];
		if (actionData == nullptr)
		{
			continue;
		}
		newState->AddExitAction(MakeShareable(actionData->CreateAction()));
	}

	return newState;
}

void UStateData::RemoveLogicAtIndex(int index)
{
	if (index <= UpdateLogics.Num())
	{
		UpdateLogics.RemoveAt(index);
	}
}
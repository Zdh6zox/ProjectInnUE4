// Fill out your copyright notice in the Description page of Project Settings.


#include "FindCounterAndSetActionData.h"
#include "StateMachineSingleton.h"
#include "StateMachineImpl/Action/FindCounterAndSetAction.h"

FActionBase* UFindCounterAndSetActionData::CreateAction()
{
	FFindCounterAndSetAction* findCounterAction = new FFindCounterAndSetAction(ActionName, CounterKey);

	return findCounterAction;
}

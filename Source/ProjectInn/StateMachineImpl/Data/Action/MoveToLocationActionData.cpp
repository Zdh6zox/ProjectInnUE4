// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToLocationActionData.h"
#include "StateMachineSingleton.h"
#include "StateMachineImpl/Action/MoveToLocationAction.h"

FActionBase* UMoveToLocationActionData::CreateAction()
{
	FMoveToLocationAction* moveToLoc = new FMoveToLocationAction(ActionName, LocationKey, IsReachThreshold);

	return moveToLoc;
}
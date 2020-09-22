// Fill out your copyright notice in the Description page of Project Settings.


#include "FindTableAndSetActionData.h"
#include "StateMachineSingleton.h"
#include "StateMachineImpl/Action/FindTableAndSetAction.h"

FActionBase* UFindTableAndSetActionData::CreateAction()
{
	FFindTableAndSetAction* findTableAction = new FFindTableAndSetAction("Find Table", TableKey);

	return findTableAction;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "StepLogicData.h"
#include "Logic/StepLogic.h"

FLogicBase* UStepLogicData::ConstructLogic()
{
	FStepLogic* stepLogic = new FStepLogic();

	return stepLogic;
}
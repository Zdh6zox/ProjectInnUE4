// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomerController.h"

void ACustomerController::MoveToPosition(FVector position)
{
	MoveToLocation(position);
}

bool ACustomerController::IsMovingTo(FVector position)
{
	if (GetMoveStatus() == EPathFollowingStatus::Moving)
	{
		if (position == GetImmediateMoveDestination())
		{
			return true;
		}
	}

	return false;
}

bool ACustomerController::IsMoveCompleted(FVector position)
{
	return true;
}
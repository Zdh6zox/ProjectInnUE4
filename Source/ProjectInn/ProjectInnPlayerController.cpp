// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ProjectInnPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "ProjectInnCharacter.h"
#include "Engine/World.h"
#include "GameFramework/PlayerInput.h"
#include "Engine/GameViewportClient.h"

AProjectInnPlayerController::AProjectInnPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void AProjectInnPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	//// keep updating the destination every tick while desired
	//if (bMoveToMouseCursor)
	//{
	//	MoveToMouseCursor();
	//}

	FVector movement = FVector::ZeroVector;
	if (IsCursorSnapOnScreenEdge(movement))
	{
		MoveCamera(movement);
	}

	FHitResult hitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, hitResult);
	if (hitResult.bBlockingHit)
	{
		AActor* hittedActor = hitResult.Actor.Get();
		if (IInputReceivableObject* receivedObject = Cast<IInputReceivableObject>(hittedActor))
		{
			if (hittedActor != m_PreFocusedObject.Get())
			{
				receivedObject->Execute_OnMouseFocusLeft(hittedActor);
				m_PreFocusedObject = hittedActor;
			}

			MouseFocusedOneParamDel.Broadcast(hittedActor);
			if (PlayerInput->WasJustReleased(EKeys::LeftMouseButton))
			{
				MouseLeftBtnClickedOneParamDel.Broadcast(hittedActor);
			}
		}
		else
		{
			m_PreFocusedObject = nullptr;
		}
	}
	else
	{
		m_PreFocusedObject = nullptr;
	}
}

void AProjectInnPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	
	//InputComponent->BindAction("SetDestination", IE_Pressed, this, &AProjectInnPlayerController::OnSetDestinationPressed);
	//InputComponent->BindAction("SetDestination", IE_Released, this, &AProjectInnPlayerController::OnSetDestinationReleased);

	//// support touch devices 
	//InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AProjectInnPlayerController::MoveToTouchLocation);
	//InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AProjectInnPlayerController::MoveToTouchLocation);

	//InputComponent->BindAction("ResetVR", IE_Pressed, this, &AProjectInnPlayerController::OnResetVR);
}

//
//void AProjectInnPlayerController::OnResetVR()
//{
//	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
//}
//
//void AProjectInnPlayerController::MoveToMouseCursor()
//{
//	if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
//	{
//		if (AProjectInnCharacter* MyPawn = Cast<AProjectInnCharacter>(GetPawn()))
//		{
//			if (MyPawn->GetCursorToWorld())
//			{
//				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
//			}
//		}
//	}
//	else
//	{
//		// Trace to see what is under the mouse cursor
//		FHitResult Hit;
//		GetHitResultUnderCursor(ECC_Visibility, false, Hit);
//
//		if (Hit.bBlockingHit)
//		{
//			// We hit something, move there
//			SetNewMoveDestination(Hit.ImpactPoint);
//		}
//	}
//}
//
//void AProjectInnPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	FVector2D ScreenSpaceLocation(Location);
//
//	// Trace to see what is under the touch location
//	FHitResult HitResult;
//	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
//	if (HitResult.bBlockingHit)
//	{
//		// We hit something, move there
//		SetNewMoveDestination(HitResult.ImpactPoint);
//	}
//}
//
//void AProjectInnPlayerController::SetNewMoveDestination(const FVector DestLocation)
//{
//	APawn* const MyPawn = GetPawn();
//	if (MyPawn)
//	{
//		float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());
//
//		// We need to issue move command only if far enough in order for walk animation to play correctly
//		if ((Distance > 120.0f))
//		{
//			UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
//		}
//	}
//}
//
//void AProjectInnPlayerController::OnSetDestinationPressed()
//{
//	// set flag to keep updating destination until released
//	bMoveToMouseCursor = true;
//}
//
//void AProjectInnPlayerController::OnSetDestinationReleased()
//{
//	// clear flag to indicate we should stop updating the destination
//	bMoveToMouseCursor = false;
//}

void AProjectInnPlayerController::MoveCamera(FVector cameraMovement)
{
	AProjectInnCharacter* player = Cast<AProjectInnCharacter>(GetPawn());
	if (player)
	{
		player->AddActorWorldOffset(cameraMovement);
	}
}

bool AProjectInnPlayerController::IsCursorSnapOnScreenEdge(FVector& cameraMovement)
{
	cameraMovement = FVector::ZeroVector;
	float screenX, screenY;
	GetMousePosition(screenX, screenY);

	bool isSnapOnEdge = false;

	int32 X = GetWorld()->GetGameViewport()->Viewport->GetSizeXY().X;
	int32 Y = GetWorld()->GetGameViewport()->Viewport->GetSizeXY().Y;

	float xRatio = screenX / X;
	float yRatio = screenY / Y;

	if (xRatio >0 && xRatio < SnapOnEdgeThreshold)
	{
		
		cameraMovement += FVector(0.0f, -CameraVelocity, 0.0f);
		isSnapOnEdge = true;
	}
	else if (xRatio > (1 - SnapOnEdgeThreshold))
	{
		cameraMovement += FVector(0.0f, CameraVelocity, 0.0f);
		isSnapOnEdge = true;
	}

	if (yRatio > 0 && yRatio < SnapOnEdgeThreshold)
	{
		cameraMovement += FVector(CameraVelocity, 0.0f, 0.0f);
		isSnapOnEdge = true;
	}
	else if (yRatio > (1 - SnapOnEdgeThreshold))
	{
		cameraMovement += FVector(-CameraVelocity, 0.0f, 0.0f);

		isSnapOnEdge = true;
	}

	return isSnapOnEdge;
}
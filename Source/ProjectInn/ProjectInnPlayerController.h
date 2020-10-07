// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Actor.h"
#include "InputReceivableObject.h"
#include "ProjectInnPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseLeftBtnClickedOneParam, AActor*, focusedReceivableActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMouseFocusedOneParam, AActor*, focusedReceivableActor);

class IInputReceivableObject;
UCLASS()
class AProjectInnPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AProjectInnPlayerController();

	UPROPERTY(EditAnywhere)
		float CameraVelocity = 5.0f;

	UPROPERTY(EditAnywhere)
		float SnapOnEdgeThreshold = 0.1f;

	UPROPERTY(BlueprintAssignable)
		FOnMouseLeftBtnClickedOneParam MouseLeftBtnClickedOneParamDel;

	UPROPERTY(BlueprintAssignable)
		FOnMouseFocusedOneParam MouseFocusedOneParamDel;


	bool IsLeftBtnPressed();
	bool WasLeftBtnReleased();
	FVector GetLocationUnderCursor();
	IInputReceivableObject* GetObjectUnderCursor();

protected:
	///** True if the controlled character should navigate to the mouse cursor. */
	//uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	///** Resets HMD orientation in VR. */
	//void OnResetVR();

	///** Navigate player to the current mouse cursor location. */
	//void MoveToMouseCursor();

	///** Navigate player to the current touch location. */
	//void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	//
	///** Navigate player to the given world location. */
	//void SetNewMoveDestination(const FVector DestLocation);

	///** Input handlers for SetDestination action. */
	//void OnSetDestinationPressed();
	//void OnSetDestinationReleased();

	void MoveCamera(FVector cameraMovement);

	bool IsCursorSnapOnScreenEdge(FVector& cameraMovement);

private:
	TWeakObjectPtr<AActor> m_PreFocusedObject;
	FVector m_HittedLocation;
};



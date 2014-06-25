// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "TwinStickShooterPlayerController.generated.h"

UCLASS()
class ATwinStickShooterPlayerController : public APlayerController
{
	GENERATED_UCLASS_BODY()

	//Current Aiming Angle initial is 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aimer)
	float AimAtAngle;

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	/** True if you want the character to always look at where the mouse is.*/
	uint32 bLookAtMouseCursor : 1;

	

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) OVERRIDE;
	virtual void SetupInputComponent() OVERRIDE;
	// End PlayerController interface

	/** Navigate player to the current mouse cursor location. */
	void MoveToMouseCursor();

	/** Navigate player to the current touch location. */
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	void OnSetDestinationPressed();
	void OnSetDestinationReleased();

	/** Rotate character to face cursor.*/
	void LookAtMouseCursor();

};



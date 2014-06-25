// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TwinStickShooter.h"
#include "TwinStickShooterCharacter.h"

ATwinStickShooterCharacter::ATwinStickShooterCharacter(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	// Set size for player capsule
	CapsuleComponent->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	CharacterMovement->bOrientRotationToMovement = true; // Rotate character to moving direction
	CharacterMovement->RotationRate = FRotator(0.f, 640.f, 0.f);
	CharacterMovement->bConstrainToPlane = true;
	CharacterMovement->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = PCIP.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = PCIP.CreateDefaultSubobject<UCameraComponent>(this, TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUseControllerViewRotation = false; // Camera does not rotate relative to arm


	bLookRight = true;
	bLookForward = true;
	AimAtAngle = 0;

}

void ATwinStickShooterCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &ATwinStickShooterCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATwinStickShooterCharacter::MoveRight);

}


void ATwinStickShooterCharacter::MoveForward(float Value)
{
	/*if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}*/

	
	// add movement in that direction
	AddMovementInput(FVector(1.f, 0.f, 0.f), Value);
}

void ATwinStickShooterCharacter::MoveRight(float Value)
{
	/*if ((Controller != NULL) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}*/
	// add movement in that direction
	AddMovementInput(FVector(0.f, 1.f, 0.f), Value);
}

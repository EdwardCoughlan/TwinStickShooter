// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TwinStickShooter.h"
#include "TwinStickShooterPlayerController.h"
#include "TwinStickShooterCharacter.h"

ATwinStickShooterPlayerController::ATwinStickShooterPlayerController(const class FPostConstructInitializeProperties& PCIP)
	: Super(PCIP)
{
	bShowMouseCursor = true;
	bLookAtMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ATwinStickShooterPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (false)
	{
		MoveToMouseCursor();
	}

	if (bLookAtMouseCursor)
	{
		LookAtMouseCursor();
	}
}

void ATwinStickShooterPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	//Default Top Down Controls
	InputComponent->BindAction("SetDestination", IE_Pressed, this, &ATwinStickShooterPlayerController::OnSetDestinationPressed);
	InputComponent->BindAction("SetDestination", IE_Released, this, &ATwinStickShooterPlayerController::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ATwinStickShooterPlayerController::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ATwinStickShooterPlayerController::MoveToTouchLocation);
}

void ATwinStickShooterPlayerController::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void ATwinStickShooterPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void ATwinStickShooterPlayerController::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void ATwinStickShooterPlayerController::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void ATwinStickShooterPlayerController::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}


void ATwinStickShooterPlayerController::LookAtMouseCursor()
{
	ATwinStickShooterCharacter* const MyPawn = (ATwinStickShooterCharacter*)GetPawn();
	if (MyPawn)
	{
		// Trace to see what is under the mouse cursor
		FHitResult Hit;
		GetHitResultUnderCursor(ECC_Visibility, false, Hit);

		//Gets player rotation
		FRotator PlayerRot = MyPawn->GetActorRotation();

		//Gets the Directional Vector Ranging from -1 to 1
		FVector PlayerDirection = PlayerRot.Vector()*-1;

		//Get The right vector for your character
		FRotator PlayerRightRot = PlayerDirection.Rotation();
		PlayerRightRot.Add(0, 90, 0);
		FVector RightVector = PlayerRightRot.Vector();

		//Gets the players current location minus the Z
		FVector PlayerLoc = MyPawn->GetActorLocation() * FVector(1, 1, 0);

		//Gets Mouse location minus the Z
		FVector MouseLoc = Hit.ImpactPoint * FVector(1, 1, 0);

		//Find the Desired angle of rotation between the Player and Mouse
		FRotator PlayerDesiredRot = (PlayerLoc - MouseLoc).Rotation();
		//float FaceToAngle = PlayerDesiredRot.Clamp().Yaw;

		//Gets a Directional Vector Ranging from -1 to 1 in screenspace for the mouse from the character
		FVector MouseDirection = PlayerDesiredRot.Vector();

		//The Aim at angle for the character
		MyPawn->AimAtAngle = ((acosf(FVector::DotProduct(PlayerDirection, MouseDirection))) * (180 / 3.1415926));
	
		//Calculate the distances from all angles
		float RDist = FVector::Dist(MouseDirection, RightVector);
		float LDist = FVector::Dist(MouseDirection, RightVector*-1);
		float FDist = FVector::Dist(MouseDirection, PlayerDirection);
		float BDist = FVector::Dist(MouseDirection, PlayerDirection * -1);

		//Set bools
		if (RDist <= LDist)
		{
			MyPawn->bLookRight = true;
		}
		else
		{
			MyPawn->bLookRight = false;
		}

		if (FDist <= BDist)
		{
			MyPawn->bLookForward = true;
		}
		else
		{
			MyPawn->bLookForward = false;
		}
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, FString::Printf(TEXT("Aim Right : %d :: Aim Forward : %d ::"), bLookRight, bLookForward));
	}
}
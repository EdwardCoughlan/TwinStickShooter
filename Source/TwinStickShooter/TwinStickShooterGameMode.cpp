// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "TwinStickShooter.h"
#include "TwinStickShooterGameMode.h"
#include "TwinStickShooterPlayerController.h"

ATwinStickShooterGameMode::ATwinStickShooterGameMode(const class FPostConstructInitializeProperties& PCIP) : Super(PCIP)
{
	// use our custom PlayerController class
	PlayerControllerClass = ATwinStickShooterPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FObjectFinder<UClass> PlayerPawnBPClass(TEXT("Class'/Game/TopDownCharacter/Blueprints/TSS_Hero.TSS_Hero_C'"));
	if (PlayerPawnBPClass.Object != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Object;

	}
}
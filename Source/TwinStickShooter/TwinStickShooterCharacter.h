// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "TwinStickShooterCharacter.generated.h"

UCLASS(Blueprintable)
class ATwinStickShooterCharacter : public ACharacter
{
	GENERATED_UCLASS_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<UCameraComponent> TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TSubobjectPtr<class USpringArmComponent> CameraBoom;

	//Current Aiming Angle initial is 0;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aimer)
	float AimAtAngle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aimer)
	bool bLookRight;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Aimer)
	bool bLookForward;



protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);



protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) OVERRIDE;
	// End of APawn interface
};


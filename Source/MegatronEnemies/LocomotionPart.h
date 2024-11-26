// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "LocomotionPart.generated.h"


USTRUCT(BlueprintType)
struct FMovementConstraints
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanWalk = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanSprint = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanJump = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool CanCrouch = true;
};


/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API ULocomotionPart : public UBodyPart
{
	GENERATED_BODY()

public:

	// TODO: move these to body for centralized logic
	// Setting walk speed, calling jump, etc would be hell from
	// individual legs

	//UFUNCTION(BlueprintNativeEvent)
	//void Walk();

	//UFUNCTION(BlueprintNativeEvent)
	//void StopWalking();

	//UFUNCTION(BlueprintNativeEvent)
	//void Sprint();

	//UFUNCTION(BlueprintNativeEvent)
	//void StopSprinting();

	//UFUNCTION(BlueprintNativeEvent)
	//void Jump();

	//UFUNCTION(BlueprintNativeEvent)
	//void StopJumping();

	//UFUNCTION(BlueprintNativeEvent)
	//void Crouch();


	//UFUNCTION(BlueprintNativeEvent)
	//void StopCrouching();


// TODO: Cut tooltip into several lines if possible
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ToolTip = "What each instance of this part will add to the attached character's movement speed. 2 legs will have this value x2"))
	float	HalfWalkSpeed = 450.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float	SprintMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float JumpForce = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float CrouchMultiplier = 0.5f;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FMovementConstraints Constraints;

};

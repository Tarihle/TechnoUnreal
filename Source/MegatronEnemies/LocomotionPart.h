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

	ULocomotionPart();

	UFUNCTION(BlueprintCallable)
	float GetBaseSpeed()			const;

	UFUNCTION(BlueprintCallable)
	float GetSprintMultiplier()		const;

	UFUNCTION(BlueprintCallable)
	float GetJumpForce()			const;

	UFUNCTION(BlueprintCallable)
	float GetCrouchMultiplier()		const;


// TODO: Cut tooltip into several lines if possible
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (ToolTip = "What each instance of this part will add to the attached character's movement speed. 2 legs will have this value x2"))
	float	BaseSpeed = 450.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float	SprintMultiplier = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float	JumpForce = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float	CrouchMultiplier = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FMovementConstraints Constraints;

};

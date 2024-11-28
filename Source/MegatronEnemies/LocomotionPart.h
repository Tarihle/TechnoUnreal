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
	bool bCanWalk = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanSprint = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanJump = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCanCrouch = true;
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

	UFUNCTION(BlueprintPure)
	float GetBaseSpeed()			const;

	UFUNCTION(BlueprintPure)
	float GetSprintMultiplier()		const;

	UFUNCTION(BlueprintPure)
	float GetJumpForce()			const;

	UFUNCTION(BlueprintPure)
	float GetCrouchMultiplier()		const;

	UFUNCTION(BlueprintPure)
	FMovementConstraints& GetMovementConstraints();

// TODO: Cut tooltip into several lines if possible
protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ToolTip = "What each instance of this part will add to the attached character's movement speed. 2 legs will have this value x2"))
	float	BaseSpeed = 450.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float	SprintMultiplier = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float	JumpForce = 200.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	float	CrouchMultiplier = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
	FMovementConstraints MovementConstraints;

};

// Fill out your copyright notice in the Description page of Project Settings.


#include "LocomotionPart.h"

ULocomotionPart::ULocomotionPart()
{
	Type = EBodyPartType::LOCOMOTION;
}

float ULocomotionPart::GetBaseSpeed() const
{
	return BaseSpeed;
}

float ULocomotionPart::GetSprintMultiplier() const
{
	return SprintMultiplier;
}

float ULocomotionPart::GetJumpForce() const
{
	return JumpForce;
}

float ULocomotionPart::GetCrouchMultiplier() const
{
	return CrouchMultiplier;
}

FMovementConstraints& ULocomotionPart::GetMovementConstraints()
{
	return MovementConstraints;
}

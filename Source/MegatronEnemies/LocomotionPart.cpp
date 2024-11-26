// Fill out your copyright notice in the Description page of Project Settings.


#include "LocomotionPart.h"

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

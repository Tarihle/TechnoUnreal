// Fill out your copyright notice in the Description page of Project Settings.


#include "LocomotionManager.h"

#include "ConnectorPart.h"
#include "LocomotionPart.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values for this component's properties
ULocomotionManager::ULocomotionManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void ULocomotionManager::Initialize(/*const TArray<class UConnectorPart*>& Connectors*/)
{
	OwnerCharacter = CastChecked<ACharacter>(GetOwner());

	float LegCount = 0;

	//for (UConnectorPart* Trunk : Connectors)
	//{
		for (ULocomotionPart* Leg : ChosenLocomotionArray)
		{
			FMovementConstraints& Constraints = Leg->GetMovementConstraints();

			++LegCount;
			bCanEverWalk &= Constraints.bCanWalk;
			bCanEverCrouch &= Constraints.bCanCrouch;
			bCanEverJump &= Constraints.bCanJump;
			bCanEverSprint &= Constraints.bCanSprint;

			if (Constraints.bCanJump)
				GlobalJumpForce += Leg->GetJumpForce();

			if (!Constraints.bCanWalk)
				continue;

			GlobalWalkSpeed += Leg->GetBaseSpeed();

			if (Constraints.bCanSprint)
				GlobalSprintMultiplier *= Leg->GetSprintMultiplier();

			if (Constraints.bCanCrouch)
				AverageCrouchMultiplier += Leg->GetCrouchMultiplier();
		}
	//}

	if (!bCanEverWalk)
		GlobalWalkSpeed = 0.f;

	if (LegCount)
		AverageCrouchMultiplier /= LegCount;

	UCharacterMovementComponent* Movement = OwnerCharacter->GetCharacterMovement();

	Movement->JumpZVelocity = GlobalJumpForce;
	Movement->MaxWalkSpeed = GlobalWalkSpeed;
	Movement->MaxWalkSpeedCrouched = GlobalWalkSpeed * AverageCrouchMultiplier;
}


void ULocomotionManager::Jump()
{
	if (bCanEverJump)
		OwnerCharacter->Jump();
}

void ULocomotionManager::StopJumping()
{
	OwnerCharacter->StopJumping();
}

void ULocomotionManager::AddArrayElement(ULocomotionPart* const& ChosenElement)
{
	ChosenLocomotionArray.Add(ChosenElement);
}

void ULocomotionManager::OnConnectorInitialized()
{
	if (++InitializedConnectorCount == ConnectorCount)
		Initialize();
}

void ULocomotionManager::SetConnectorCount(int32 Count)
{
	ConnectorCount = Count;
}

// Called when the game starts
void ULocomotionManager::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void ULocomotionManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULocomotionManager::OnPartDestroyed(ULocomotionPart* Part)
{
	GlobalWalkSpeed -= Part->GetBaseSpeed();
	GlobalSprintMultiplier /= Part->GetSprintMultiplier();
	GlobalJumpForce -= Part->GetJumpForce();

	UCharacterMovementComponent* Movement = OwnerCharacter->GetCharacterMovement();

	Movement->JumpZVelocity = GlobalJumpForce;
	Movement->MaxWalkSpeed = GlobalWalkSpeed;

}

void ULocomotionManager::Sprint()
{
	if (bCanEverSprint)
		OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GlobalWalkSpeed * GlobalSprintMultiplier;
}

void ULocomotionManager::StopSprinting()
{
	OwnerCharacter->GetCharacterMovement()->MaxWalkSpeed = GlobalWalkSpeed;
}

void ULocomotionManager::Crouch()
{
	if (bCanEverCrouch)
		OwnerCharacter->Crouch();
}

void ULocomotionManager::StopCrouching()
{
	OwnerCharacter->UnCrouch();
}


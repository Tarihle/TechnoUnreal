// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LocomotionManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEGATRONENEMIES_API ULocomotionManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ULocomotionManager();


	void Initialize(const TArray<class UConnectorPart*>& Connectors);


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnPartDestroyed(class ULocomotionPart* Part);

	UFUNCTION(BlueprintCallable)
	void Sprint();

	UFUNCTION(BlueprintCallable)
	void StopSprinting();

	UFUNCTION(BlueprintCallable)
	void Crouch();

	UFUNCTION(BlueprintCallable)
	void StopCrouching();

	UFUNCTION(BlueprintCallable)
	void Jump();

	UFUNCTION(BlueprintCallable)
	void StopJumping();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TObjectPtr<class ACharacter>	OwnerCharacter;

private:

	float	GlobalWalkSpeed = 0.f;
	float	GlobalSprintMultiplier = 1.f;
	float	AverageCrouchMultiplier = 0.f;
	float   GlobalJumpForce = 0.f;

	bool	bCanEverCrouch  = true;
	bool	bCanEverJump    = true;
	bool	bCanEverSprint  = true;
	bool	bCanEverWalk    = true;
};

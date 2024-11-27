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

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void DecreaseGlobalSpeeds(float WalkSpeed, float SprintModifier);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	float	GlobalWalkSpeed = 0.f;
	float	GlobalSprintMultiplier = 1.f;
	float	AverageCrouchMultiplier = 0.5f;
};

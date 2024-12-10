// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePartManager.h"
#include "LocomotionManager.generated.h"

UCLASS()
class MEGATRONENEMIES_API ULocomotionManager : public UBasePartManager
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	ULocomotionManager();

	void Initialize(/*const TArray<class UConnectorPart*>& Connectors*/);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

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

	void OnPartDestroyed(class ULocomotionPart* Part);

	void OnConnectorInitialized();
	void SetConnectorCount(int32 Count);

	UFUNCTION(BlueprintPure)
	class ULocomotionPart* GetRandomPart();

	UFUNCTION(BlueprintPure)
	TArray<class ULocomotionPart*> GetAllPartsWithTaskByClass(TSubclassOf<class UMegatronTask> TaskClass);

	UFUNCTION(BlueprintPure)
	TArray<class ULocomotionPart*> GetAllPartsWithTaskByTag(struct FGameplayTag Tag);

  protected:
	// Called when the game starts
	virtual void BeginPlay() override;

  private:
	float GlobalWalkSpeed = 0.f;
	float GlobalSprintMultiplier = 1.f;
	float AverageCrouchMultiplier = 0.f;
	float GlobalJumpForce = 0.f;

	int32 InitializedConnectorCount = 0;
	int32 ConnectorCount = 0;
	
	bool bCanEverCrouch = true;
	bool bCanEverJump = true;
	bool bCanEverSprint = true;
	bool bCanEverWalk = true;
};

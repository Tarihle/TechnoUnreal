// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePartManager.h"
#include "Components/ActorComponent.h"
#include "PerceptionManager.generated.h"

UCLASS()
class MEGATRONENEMIES_API UPerceptionManager : public UBasePartManager
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	UPerceptionManager();

  protected:
	// Called when the game starts
	virtual void BeginPlay() override;

  public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	TArray<class AActor*>	GetAllPerceivedActors();

	UFUNCTION(BlueprintPure)
	TArray<class AActor*> GetSeenActors();

	UFUNCTION(BlueprintPure)
	TArray<class AActor*> GetHeardActors();

	UFUNCTION(BlueprintPure)
	TArray<class AActor*> GetTouchedActors();
};

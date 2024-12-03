// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MegatronManager.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MEGATRONENEMIES_API UMegatronManager : public UActorComponent
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	UMegatronManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	class UInteractionManager* GetInteraction();

	UFUNCTION(BlueprintPure)
	class ULocomotionManager* GetLocomotion();

	UFUNCTION(BlueprintPure)
	class UPerceptionManager* GetPerception();

  protected:
	// Called when the game starts
	virtual void BeginPlay() override;

  private:
	TObjectPtr<class UInteractionManager> InteractionManager;
	TObjectPtr<class ULocomotionManager>  LocomotionManager;
	TObjectPtr<class UPerceptionManager>  PerceptionManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Megatron", meta = (AllowPrivateAccess = "true"))
	TArray<class UConnectorPart*> Connectors;

	// TODO: add possible connectors

	float MaxHealth = 0.f;

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Megatron")
	int32 CharacterLevel = 1;
};

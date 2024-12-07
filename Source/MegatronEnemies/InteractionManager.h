// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePartManager.h"
#include "Components/ActorComponent.h"
#include "InteractionManager.generated.h"

UCLASS()
class MEGATRONENEMIES_API UInteractionManager : public UBasePartManager
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UInteractionManager();

	UFUNCTION(BlueprintPure)
	class UInteractionPart* GetRandomPart();
	
	UFUNCTION(BlueprintPure)
	TArray<class UInteractionPart*> GetAllPartsWithTaskByClass(TSubclassOf<class UMegatronTask> TaskClass);

	UFUNCTION(BlueprintPure)
	TArray<class UInteractionPart*> GetAllPartsWithTaskByTag(struct FGameplayTag Tag);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};

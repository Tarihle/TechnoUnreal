// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "ConnectorPart.generated.h"

/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API UConnectorPart : public UBodyPart
{
	GENERATED_BODY()

public:

	UConnectorPart();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parts")
	TArray<class ULocomotionPart*>  LocomotionParts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parts")
	TArray<class UPerceptionPart*>  PerceptionParts;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Parts")
	TArray<class UInteractionPart*> InteractionParts;

};

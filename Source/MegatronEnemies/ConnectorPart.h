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

protected:

	TArray<class ULocomotionPart*>  LocomotionParts;
	TArray<class UPerceptionPart*>  PerceptionParts;
	TArray<class UInteractionPart*> InteractionParts;

};

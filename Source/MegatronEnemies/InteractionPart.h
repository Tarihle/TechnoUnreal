// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "InteractionPart.generated.h"

/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API UInteractionPart : public UBodyPart
{
	GENERATED_BODY()

public:
	
	UInteractionPart();

protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Behavior)
	float AttackDamage = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Behavior)
	float ActionRange = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Behavior)
	float ActionSpeedIncrement = 0.f;
};

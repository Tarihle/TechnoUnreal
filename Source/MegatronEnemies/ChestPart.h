// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "ChestPart.generated.h"

/**
 * 
 */
UCLASS()
class MEGATRONENEMIES_API UChestPart : public UBodyPart
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float MaxHealth = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	int Level = 0;

public:
	UChestPart();
};

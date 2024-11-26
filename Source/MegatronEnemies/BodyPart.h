// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "BodyPart.generated.h"

/**
 * 
 */
UCLASS()
class MEGATRONENEMIES_API UBodyPart : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float LocalHealth = 0.f;

public:
	UBodyPart();
};

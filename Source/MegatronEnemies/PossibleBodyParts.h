// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PossibleBodyParts.generated.h"

class UBodyPart;

/**
 * 
 */
UCLASS()
class MEGATRONENEMIES_API UPossibleBodyParts : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyParts)
	TArray<TSubclassOf<UBodyPart>> BodyPartsArray;

public:
	UPossibleBodyParts();

	TArray<TSubclassOf<UBodyPart>> GetPartArray();
};

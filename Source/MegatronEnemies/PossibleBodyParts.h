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

	int32 TrueSize = 0;

  public:
	UPossibleBodyParts();
	virtual void PostLoad() override;

	TArray<TSubclassOf<UBodyPart>> GetPartArray();
	int							   ContainsByName(TSubclassOf<UBodyPart> Part);
	bool						   RemoveByName(TSubclassOf<UBodyPart> Part);
	int							   GetArraySize();
	void						   ReinitArraySize();
};

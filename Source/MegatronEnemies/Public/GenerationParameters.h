// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../BodyPart.h"
#include "GenerationParameters.generated.h"

USTRUCT(BlueprintType)
struct FWeightedParam
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBodyPart> Condition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBodyPart> Reactor;

	FWeightedParam();

	bool GetConditionFilledState();
	void SetConditionFilledState(bool State);
	EBodyPartType GetReactorBodyPartType();

  private:
	bool ConditionFilled = false;
};

/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API UGenerationParameters : public UPrimaryDataAsset
{
	GENERATED_BODY()

  public:
	UGenerationParameters();

	TArray<FWeightedParam> GetWhiteList();

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WhiteList)
	TArray<FWeightedParam> WhiteList;
};

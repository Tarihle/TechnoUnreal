// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../BodyPart.h"
#include "GenerationParameters.generated.h"

USTRUCT(BlueprintType)
struct FWeightedReactor
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0, ClampMax = 100), meta = (Units = "Percent"))
	int32 Weight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBodyPart> Reactor;

	FWeightedReactor();
};

USTRUCT(BlueprintType)
struct FWeightedParam
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBodyPart> Condition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FWeightedReactor> ReactorList;

	FWeightedParam();

	bool		  GetConditionFilledState();
	void		  SetConditionFilledState(bool State);
	EBodyPartType GetReactorBodyPartType(int Index);
	int32		  GetReactorWeight(int Index);

  private:
	bool ConditionFilled = false;
};

USTRUCT(BlueprintType)
struct FDefendedParam
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UBodyPart> Condition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UBodyPart>> Reactions;

	FDefendedParam();

	bool GetConditionFilledState();
	void SetConditionFilledState(bool State);

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
	TArray<FDefendedParam> GetBlackList();

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WhiteList)
	TArray<FWeightedParam> WhiteList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = WhiteList)
	TArray<FDefendedParam> BlackList;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "ConnectorPart.generated.h"

#define USEINTERACTION 0b001
#define USELOCOMOTION 0b010
#define USEPERCEPTION 0b100

USTRUCT(BlueprintType)
struct FIndividualBodyPart
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ForceRebuildProperty = "DefaultPart"))
	TSubclassOf<UBodyPart> DefaultPart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UPossibleBodyParts> PossibleParts;

	FIndividualBodyPart();
};

/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API UConnectorPart : public UBodyPart
{
	GENERATED_BODY()

  public:
	UConnectorPart();
	void InitializeComponent() override;

  protected:
	TObjectPtr<class ACharacter>		  OwnerCharacter;
	TObjectPtr<class ULocomotionManager>  LocomotionManagerRef;
	TObjectPtr<class UInteractionManager> InteractionManagerRef;
	TObjectPtr<class UPerceptionManager>  PerceptionManagerRef;

	TArray<class USkeletalMesh*> PossibleMeshes;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseInteraction = false;
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseLocomotion = false;
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUsePerception = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyParts, meta = (EditCondition = "bUseInteraction"))
	TArray<FIndividualBodyPart> InteractionParts;
	int							InteractionArrayIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyParts, meta = (EditCondition = "bUseLocomotion"))
	TArray<FIndividualBodyPart> LocomotionParts;
	int							LocomotionArrayIndex = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = BodyParts, meta = (EditCondition = "bUsePerception"))
	TArray<FIndividualBodyPart> PerceptionParts;
	int							PerceptionArrayIndex = 0;

	TArray<struct FWeightedParam> WhiteListRef;
	TArray<struct FDefendedParam> BlackListRef;

	void BeginPlay() override;
	void EndPlay(EEndPlayReason::Type Reason) override;

	void GenerateIndividualPart(TArray<FIndividualBodyPart> PartsArray, EBodyPartType PartType, int& ArrayIndex);
	void ReinitPossibleParts(TArray<FIndividualBodyPart> PartsArray);
	void RemoveBlackListedParts(int ArrayIndex);
	void ValidateListsCondition(UBodyPart* LoadedPart);
	void SetMeshes(UBodyPart* LoadedPart, EBodyPartType PartType);
};

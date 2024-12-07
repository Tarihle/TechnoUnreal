// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "ConnectorPart.generated.h"

USTRUCT(BlueprintType)
struct FIndividualBodyPart
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite/*, meta = (UseComponentPicker, AllowedClasses = "SkeletalMeshComponent", DisallowedClasses = "StaticMeshComponent")*/)
	FComponentReference MeshReference;

	UPROPERTY(EditAnywhere, meta = (ForceRebuildProperty = "DefaultPart"))
	TSoftClassPtr<class UBodyPart> DefaultPart;
	UPROPERTY(EditAnywhere)
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
	TObjectPtr<class ACharacter> OwnerCharacter;
	TObjectPtr<class ULocomotionManager> LocomotionManagerRef;

	TArray<class USkeletalMesh*> PossibleMeshes;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseInteraction = false;
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseLocomotion = false;
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUsePerception = false;

	UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = BodyParts, meta = (EditCondition = "bUseInteraction"))
	TArray<FIndividualBodyPart> InteractionParts;
	UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = BodyParts, meta = (EditCondition = "bUseLocomotion"))
	TArray<FIndividualBodyPart> LocomotionParts;
	UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = BodyParts, meta = (EditCondition = "bUsePerception"))
	TArray<FIndividualBodyPart> PerceptionParts;

	void BeginPlay() override;

	/* These functions are basically the same, we separate them for usability and because we have 3 different
	 * "IndividualPart" structs */
	UFUNCTION()
	void GenerateInteractionParts();
	UFUNCTION()
	void GenerateLocomotionParts();
	UFUNCTION()
	void GeneratePerceptionParts();
};

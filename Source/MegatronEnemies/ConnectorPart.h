// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "ConnectorPart.generated.h"

/* I've tried to use unions to have a single struct but without success because I suck at my job and everything I do, */
/* So if you manage to make it work, congrats *slow claps* */
USTRUCT(BlueprintType)
struct FIndividualInteraction
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite/*, meta = (UseComponentPicker, AllowedClasses = "SkeletalMeshComponent", DisallowedClasses = "StaticMeshComponent")*/)
	FComponentReference MeshReference;

	UPROPERTY(EditAnywhere, meta = (ForceRebuildProperty = "DefaultInteractionPart"))
	TObjectPtr<class UInteractionPart> DefaultInteractionPart;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPossibleBodyParts> PossibleInteractions;

	FIndividualInteraction();
};

USTRUCT(BlueprintType)
struct FIndividualLocomotion
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite/*, meta = (UseComponentPicker, AllowedClasses = "SkeletalMeshComponent", DisallowedClasses = "StaticMeshComponent")*/)
	FComponentReference MeshReference;

	UPROPERTY(EditAnywhere, meta = (ForceRebuildProperty = "DefaultLocomotionPart"))
	TObjectPtr<class ULocomotionPart> DefaultLocomotionPart;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPossibleBodyParts> PossibleLocomotions;

	FIndividualLocomotion();
};

USTRUCT(BlueprintType)
struct FIndividualPerception
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite/*, meta = (UseComponentPicker, AllowedClasses = "SkeletalMeshComponent", DisallowedClasses = "StaticMeshComponent")*/)
	FComponentReference MeshReference;

	UPROPERTY(EditAnywhere, meta = (ForceRebuildProperty = "DefaultPerceptionPart"))
	TObjectPtr<class UPerceptionPart> DefaultPerceptionPart;
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UPossibleBodyParts> PossiblePerceptions;

	FIndividualPerception();
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
	
	TArray<class USkeletalMesh*> PossibleMeshes;
	
	TObjectPtr<class ACharacter> OwnerCharacter;
	TObjectPtr<class ULocomotionManager> LocomotionManagerRef;
	TObjectPtr<class UInteractionManager> InteractionManagerRef;
	TObjectPtr<class UPerceptionManager> PerceptionManagerRef;


	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseInteraction = false;
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseLocomotion = false;
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUsePerception = false;

	UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = BodyParts, meta = (EditCondition = "bUseInteraction"))
	TArray<FIndividualInteraction> InteractionParts;
	UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = BodyParts, meta = (EditCondition = "bUseLocomotion"))
	TArray<FIndividualLocomotion> LocomotionParts;
	UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = BodyParts, meta = (EditCondition = "bUsePerception"))
	TArray<FIndividualPerception> PerceptionParts;

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

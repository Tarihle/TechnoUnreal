// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "ConnectorPart.generated.h"

/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API UConnectorPart : public UBodyPart
{
	GENERATED_BODY()

public:

	UConnectorPart();

protected:
	TObjectPtr<class ACharacter> CharacterOwnerRef;

	TArray<class USkeletalMesh*> PossibleMeshes;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseInteraction = false;
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseLocomotion = false;
	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUsePerception = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyParts, meta = (EditCondition = "bUseInteraction"))
	TArray<class UInteractionPart*> InteractionParts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyParts, meta = (EditCondition = "bUseLocomotion"))
	TArray<class ULocomotionPart*>  LocomotionParts;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyParts, meta = (EditCondition = "bUsePerception"))
	TArray<class UPerceptionPart*>  PerceptionParts;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PartsPossibility, meta = (EditCondition = "bUseInteraction"))
	TObjectPtr<class UPossibleBodyParts> PossibleInteractions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PartsPossibility, meta = (EditCondition = "bUseLocomotion"))
	TObjectPtr<class UPossibleBodyParts> PossibleLocomotions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PartsPossibility, meta = (EditCondition = "bUsePerception"))
	TObjectPtr<class UPossibleBodyParts> PossiblePerceptions;

	void BeginPlay() override;
};

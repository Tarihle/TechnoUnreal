// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BodyPartManager.generated.h"

class UChestPart;
class UPossibleBodyParts;
class UPerceptionPart;
class UInteractionPart;
class ULocomotionPart;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEGATRONENEMIES_API UBodyPartManager : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseBody = false;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUsePerception = false;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseInteraction = false;

	UPROPERTY(EditAnywhere, meta = (InlineEditConditionToggle))
	bool bUseLocomotion = false;

	/* Default "Body", if set to none, a random one will be selected from "PossibleBodies" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Parts, meta = (EditCondition = "bUseBody"))
	TObjectPtr<UChestPart> Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PartsPossibility, meta = (EditCondition = "bUseBody"))
	TObjectPtr<UPossibleBodyParts> PossibleBodies;

	/* Default "Perception", if set to none, a random one will be selected from "PossibleInteraction" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyParts, meta = (EditCondition = "bUsePerception"))
	TSubclassOf<UPerceptionPart> Perception;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PartsPossibility, meta = (EditCondition = "bUsePerception"))
	TObjectPtr<UPossibleBodyParts> PossiblePerceptions;

	/* Default "Interaction", if set to none, a random one will be selected from "PossibleInteraction" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyParts, meta = (EditCondition = "bUseInteraction"))
	TSubclassOf<UInteractionPart> Interaction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PartsPossibility, meta = (EditCondition = "bUseInteraction"))
	TObjectPtr<UPossibleBodyParts> PossibleInteractions;

	/* Default "Locomotion", if set to none, a random one will be selected from "PossibleLocomotion" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyParts, meta = (EditCondition = "bUseLocomotion"))
	TSubclassOf<ULocomotionPart> Locomotion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PartsPossibility, meta = (EditCondition = "bUseLocomotion"))
	TObjectPtr<UPossibleBodyParts> PossibleLocomotions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite/*, meta = (UseComponentPicker, AllowedClasses = "SkeletalMeshComponent", DisallowedClasses = "StaticMeshComponent")*/)
	FComponentReference MeshReference;

public:	
	// Sets default values for this component's properties
	UBodyPartManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

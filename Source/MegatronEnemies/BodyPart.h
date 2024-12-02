// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "BodyPart.generated.h"


UENUM(BlueprintType)
enum class EBodyPartType : uint8
{
	INVALID,
	CONNECTOR,
	LOCOMOTION,
	INTERACTION,
	PERCEPTION
};

/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API UBodyPart : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float			LocalHealth = 0.f;
	EBodyPartType	Type = EBodyPartType::INVALID;

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite/*, meta = (UseComponentPicker, AllowedClasses = "SkeletalMeshComponent", DisallowedClasses = "StaticMeshComponent")*/)
	FComponentReference MeshReference;

	UBodyPart();

	static bool IsInteraction(UBodyPart* Part);
	static bool IsConnector(UBodyPart* Part);
	static bool IsPerception(UBodyPart* Part);
	static bool IsLocomotion(UBodyPart* Part);
};

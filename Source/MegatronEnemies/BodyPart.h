// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameplayTagContainer.h"
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


USTRUCT(BlueprintType)
struct FActionIndex
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class UMegatronTask> Class;
	int32							 Index;
};

/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API UBodyPart : public USkeletalMeshComponent
{
	GENERATED_BODY()

  protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Behavior)
	TMap<FGameplayTag, FActionIndex> ActionMap;

	/* Ugly workaround to allow designers to pick action classes
	 * from the editor.*/
	// TODO: make UMegatronTask compatible with Instnaced UPROPERTY specifier 
	UPROPERTY()
	TArray<class UMegatronTask*> Actions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Stats)
	float LocalHealth = 0.f;

	EBodyPartType Type = EBodyPartType::INVALID;

  protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

  public:
	UBodyPart();
	virtual void InitializeComponent() override;

	UPROPERTY(BlueprintReadOnly, Category = MeshRef)
	TObjectPtr<USkeletalMeshComponent> RefMeshComponent;

	/* Get action from Gameplay Tag as specified in ActionMap. Returns Null on failure */
	UFUNCTION(BlueprintPure)
	class UMegatronTask* GetTask(FGameplayTag Tag);

	UFUNCTION(BlueprintPure)
	bool HasTaskByTag(FGameplayTag Tag);


	UFUNCTION(BlueprintPure)
	bool HasTaskByClass(TSubclassOf<class UMegatronTask> Class);


	static bool IsInteraction(UBodyPart* Part);
	static bool IsConnector(UBodyPart* Part);
	static bool IsPerception(UBodyPart* Part);
	static bool IsLocomotion(UBodyPart* Part);

	static bool IsInteraction(TSubclassOf<UBodyPart> Part);
	static bool IsConnector(TSubclassOf<UBodyPart> Part);
	static bool IsPerception(TSubclassOf<UBodyPart> Part);
	static bool IsLocomotion(TSubclassOf<UBodyPart> Part);
};

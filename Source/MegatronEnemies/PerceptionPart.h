// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "PerceptionPart.generated.h"

// Not in use for now.
// TODO: Find a way to enable/disable some senses based on these variables
USTRUCT(BlueprintType)
struct FPerceptionConstraints
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanSee = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanHear = true;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bCanFeelTouch = true;
};

UENUM(BlueprintType)
enum class EPerceptionID : uint8
{
	SIGHT,
	HEARING,
	TOUCH
};

/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API UPerceptionPart : public UBodyPart
{
	GENERATED_BODY()

public:
	
	virtual void InitializeComponent() override;

	UFUNCTION(BlueprintCallable)
	bool IsSenseEnabled(EPerceptionID Sense) const;
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void EnableSight();
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void DisableSight();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void EnableHearing();
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void DisableHearing();

	UFUNCTION(BlueprintCallable, CallInEditor)
	void EnableTouch();
	
	UFUNCTION(BlueprintCallable, CallInEditor)
	void DisableTouch();

	UFUNCTION(BlueprintCallable)
	TArray<class AActor*> GetAllPerceivedActors() const;

	UFUNCTION(BlueprintCallable)
	TArray<class AActor*> GetSeenActors() const;

	UFUNCTION(BlueprintCallable)
	TArray<class AActor*> GetHeardActors() const;

	UFUNCTION(BlueprintCallable)
	TArray<class AActor*> GetTouchedActors() const;
	
protected:

	void SetSenseEnabled(EPerceptionID Sense, bool bEnabled);
	
	TArray<class AActor*> GetSensedActors(const TSubclassOf<class UAISense>& Sense) const;

	virtual void BeginPlay() override;
	
	
	TObjectPtr<class UAIPerceptionComponent>  PerceptionComponent = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Behavior)
	FPerceptionConstraints Constraints;

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Instanced, Category = Behavior, meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<class UAISenseConfig>> Senses;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BodyPart.h"
#include "InteractionPart.generated.h"

/**
 *
 */
UCLASS()
class MEGATRONENEMIES_API UInteractionPart : public UBodyPart
{
	GENERATED_BODY()

public:

	UInteractionPart();

	UFUNCTION(BlueprintNativeEvent)
	void ExecuteAction();

	UFUNCTION(BlueprintNativeEvent)
	void StopAction();

	UFUNCTION(BlueprintCallable)
	bool IsExecutingAction() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float AttackDamage = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float ActionRange = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	float ActionSpeedIncrement = 0.f;


private:

	bool bIsExecutingAction = false;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BodyPartManager.generated.h"

class UBodyPart;
class UPossibleBodyParts;

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MEGATRONENEMIES_API UBodyPartManager : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//TODO Replace with specific class for body
	/* Default "Body", if set to null, a random one will be selected from "PossibleBodies" */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = BodyParts)
	TSubclassOf<UBodyPart> Body;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PartsPossibility)
	TObjectPtr<UPossibleBodyParts> PossibleBodies;

public:	
	// Sets default values for this component's properties
	UBodyPartManager();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

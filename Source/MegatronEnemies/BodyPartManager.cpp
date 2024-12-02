// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyPartManager.h"
#include "ChestPart.h"
#include "PossibleBodyParts.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UBodyPartManager::UBodyPartManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	//SkeletalMergeTool = CreateDefaultSubobject<USkeletalMergingLibrary>(FName("SkelMeshMerge"));
	 
	// ...
}

// Called when the game starts
void UBodyPartManager::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerRef = Cast<ACharacter>(GetOwner());
	if (OwnerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("OwnerRef"));
		USkeletalMeshComponent* Ref = Cast<USkeletalMeshComponent>(MeshReference.GetComponent(OwnerRef));
		if (Ref)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ref"));
			if (Body)
			{
				UE_LOG(LogTemp, Warning, TEXT("%s"), *Body.GetName());
				Ref->SetSkeletalMesh(Body->SkeletalMesh);
			}
			else if (PossibleBodies)
			{
				int32 Index = FMath::RandRange(0, PossibleBodies->GetPartArray().Num() - 1);
				UE_LOG(LogTemp, Warning, TEXT("PossibleBodies: %d"), Index);
				Ref->SetSkeletalMesh(PossibleBodies->GetPartArray()[Index]->SkeletalMesh);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Oskour"));
			}
		}
	}

	// ...
	
}

// Called every frame
void UBodyPartManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


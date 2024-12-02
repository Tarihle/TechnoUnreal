// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectorPart.h"
#include "PossibleBodyParts.h"
#include "ChestPart.h"
#include "InteractionPart.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

UConnectorPart::UConnectorPart()
{
	Type = EBodyPartType::CONNECTOR;

	CharacterOwnerRef = Cast<ACharacter>(GetOwner());
}

void UConnectorPart::BeginPlay()
{
	Super::BeginPlay();

	if (!CharacterOwnerRef)
	{
		return;
	}

	if (bUseInteraction && InteractionParts.Num() > 0)
	{
		for (int i = 0; i < InteractionParts.Num(); i++)
		{
			USkeletalMeshComponent* Ref = Cast<USkeletalMeshComponent>(InteractionParts[i].MeshReference.GetComponent(CharacterOwnerRef));
			if (!Ref)
			{
				UE_LOG(LogTemp, Error, TEXT("No Ref"));
			}

			if (InteractionParts[i].DefaultInteractionPart)
			{
				Ref->SetSkeletalMesh(InteractionParts[i].DefaultInteractionPart->SkeletalMesh);
			}
			else if (InteractionParts[i].PossibleInteractions)
			{
				int32 Index = FMath::RandRange(0, InteractionParts[i].PossibleInteractions->GetPartArray().Num() - 1);

				Ref->SetSkeletalMesh(InteractionParts[i].PossibleInteractions->GetPartArray()[Index]->SkeletalMesh);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Oskour"));
			}
		}
	}
}

FIndividualInteraction::FIndividualInteraction()
{
}

FIndividualLocomotion::FIndividualLocomotion()
{
}

FIndividualPerception::FIndividualPerception()
{
}

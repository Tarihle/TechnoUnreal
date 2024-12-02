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
		USkeletalMeshComponent* Ref = Cast<USkeletalMeshComponent>(InteractionParts[0].MeshReference.GetComponent(CharacterOwnerRef));
		if (!Ref)
		{
			UE_LOG(LogTemp, Error, TEXT("No Ref"));
		}
		else if (InteractionParts[0].DefaultInteractionPart)
		{
			Ref->SetSkeletalMesh(InteractionParts[0].DefaultInteractionPart->SkeletalMesh);
		}
		else if (InteractionParts[0].PossibleInteractions)
		{
			int32 Index = FMath::RandRange(0, InteractionParts[0].PossibleInteractions->GetPartArray().Num() - 1);

			//if (!InteractionParts[0].PossibleInteractions->GetPartArray()[Index]->StaticClass()->IsChildOf(UInteractionPart::StaticClass()))
			//{
			//	UE_LOG(LogTemp, Error, TEXT("Class : %s"), *(InteractionParts[0].PossibleInteractions->GetPartArray()[Index]->StaticClass()->GetFName()).ToString());
			//}
			//UInteractionPart* CastPart = Cast<UInteractionPart>(InteractionParts[0].PossibleInteractions->GetPartArray()[Index]);
			//if (CastPart)
			//{
			//	Ref->SetSkeletalMesh(CastPart->SkeletalMesh);
			//}
			//else
			//{
			//	UE_LOG(LogTemp, Error, TEXT("No Cast, Index = %d"), Index);
			//}
			Ref->SetSkeletalMesh(InteractionParts[0].PossibleInteractions->GetPartArray()[Index]->SkeletalMesh);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Oskour"));
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

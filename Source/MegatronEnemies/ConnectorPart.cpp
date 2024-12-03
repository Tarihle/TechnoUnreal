// Fill out your copyright notice in the Description page of Project Settings.

#include "ConnectorPart.h"

#include "InteractionPart.h"
#include "LocomotionManager.h"
#include "LocomotionPart.h"
#include "MegatronManager.h"
#include "PerceptionPart.h"
#include "PossibleBodyParts.h"

#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"

UConnectorPart::UConnectorPart()
{
	Type = EBodyPartType::CONNECTOR;
}

void UConnectorPart::InitializeComponent()
{
	Super::InitializeComponent();

	OwnerCharacter = Cast<ACharacter>(GetOwner());

	if (OwnerCharacter->GetComponentByClass<UMegatronManager>())
	{
		LocomotionManagerRef = OwnerCharacter->GetComponentByClass<UMegatronManager>()->GetLocomotion();
		UE_LOG(LogTemp, Warning, TEXT("LocomotionManagerRef set"));
	}
}

void UConnectorPart::BeginPlay()
{
	Super::BeginPlay();

	if (!OwnerCharacter)
	{
		return;
	}

	GenerateInteractionParts();
	GenerateLocomotionParts();
	GeneratePerceptionParts();

	LocomotionManagerRef->OnConnectorInitialized();
}

void UConnectorPart::GenerateInteractionParts()
{
	if (bUseInteraction && InteractionParts.Num() > 0)
	{
		for (int i = 0; i < InteractionParts.Num(); i++)
		{
			USkeletalMeshComponent* Ref =
				Cast<USkeletalMeshComponent>(InteractionParts[i].MeshReference.GetComponent(OwnerCharacter));
			if (!Ref)
			{
				UE_LOG(LogTemp, Error, TEXT("No Ref"));
			}

			else if (InteractionParts[i].DefaultInteractionPart)
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
	UE_LOG(LogTemp, Warning, TEXT("Generated Interactions"));
}

void UConnectorPart::GenerateLocomotionParts()
{
	if (bUseLocomotion && LocomotionParts.Num() > 0)
	{
		for (int i = 0; i < LocomotionParts.Num(); i++)
		{
			USkeletalMeshComponent* Ref =
				Cast<USkeletalMeshComponent>(LocomotionParts[i].MeshReference.GetComponent(OwnerCharacter));
			if (!Ref)
			{
				UE_LOG(LogTemp, Error, TEXT("No Ref"));
			}

			else if (LocomotionParts[i].DefaultLocomotionPart)
			{
				Ref->SetSkeletalMesh(LocomotionParts[i].DefaultLocomotionPart->SkeletalMesh);
				LocomotionManagerRef->AddArrayElement(LocomotionParts[i].DefaultLocomotionPart);
			}
			else if (LocomotionParts[i].PossibleLocomotions)
			{
				int32 Index = FMath::RandRange(0, LocomotionParts[i].PossibleLocomotions->GetPartArray().Num() - 1);

				Ref->SetSkeletalMesh(LocomotionParts[i].PossibleLocomotions->GetPartArray()[Index]->SkeletalMesh);
				ULocomotionPart* CastPart = Cast<ULocomotionPart>(LocomotionParts[i].PossibleLocomotions->GetPartArray()[Index]);
				LocomotionManagerRef->AddArrayElement(CastPart);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Oskour"));
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Generated Locomotions"));
}

void UConnectorPart::GeneratePerceptionParts()
{
	if (bUsePerception && PerceptionParts.Num() > 0)
	{
		for (int i = 0; i < PerceptionParts.Num(); i++)
		{
			USkeletalMeshComponent* Ref =
				Cast<USkeletalMeshComponent>(PerceptionParts[i].MeshReference.GetComponent(OwnerCharacter));
			if (!Ref)
			{
				UE_LOG(LogTemp, Error, TEXT("No Ref"));
			}

			else if (PerceptionParts[i].DefaultPerceptionPart)
			{
				Ref->SetSkeletalMesh(PerceptionParts[i].DefaultPerceptionPart->SkeletalMesh);
			}
			else if (PerceptionParts[i].PossiblePerceptions)
			{
				int32 Index = FMath::RandRange(0, PerceptionParts[i].PossiblePerceptions->GetPartArray().Num() - 1);

				Ref->SetSkeletalMesh(PerceptionParts[i].PossiblePerceptions->GetPartArray()[Index]->SkeletalMesh);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Oskour"));
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Generated Perceptions"));
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

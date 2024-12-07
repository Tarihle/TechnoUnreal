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
}

void UConnectorPart::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		return;
	}

	if (OwnerCharacter->GetComponentByClass<UMegatronManager>())
	{
		LocomotionManagerRef = OwnerCharacter->GetComponentByClass<UMegatronManager>()->GetLocomotion();
		// UE_LOG(LogTemp, Warning, TEXT("LocomotionManagerRef set for %s"), *this->GetFName().ToString());
		GenerateInteractionParts();
		GenerateLocomotionParts();
		GeneratePerceptionParts();

		LocomotionManagerRef->OnConnectorInitialized();
	}
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
			else if (InteractionParts[i].DefaultPart)
			{
				Ref->SetSkeletalMesh(InteractionParts[i].DefaultPart->GetDefaultObject<UInteractionPart>()->GetSkeletalMeshAsset());
				UClass*						 DefaultInteractionLoaded = InteractionParts[i].DefaultPart.LoadSynchronous();
				TObjectPtr<UInteractionPart> InteractionPartCreated = Cast<UInteractionPart>(
					GetOwner()->AddComponentByClass(DefaultInteractionLoaded, false, FTransform::Identity, false));
				// if (InteractionPartCreated)
				//{
				//	InteractionManagerRef->AddArrayElement(InteractionPartCreated);
				// }
			}
			else if (InteractionParts[i].PossibleParts)
			{
				int32 Index = FMath::RandRange(0, InteractionParts[i].PossibleParts->GetPartArray().Num() - 1);

				Ref->SetSkeletalMesh(InteractionParts[i].PossibleParts->GetPartArray()[Index]->GetSkeletalMeshAsset());
				UInteractionPart* CastPart = Cast<UInteractionPart>(InteractionParts[i].PossibleParts->GetPartArray()[Index]);
				// if (CastPart)
				//{
				//	InteractionManagerRef->AddArrayElement(CastPart);
				// }
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Oskour"));
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Generated Interactions for %s"), *this->GetFName().ToString());
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
			else if (LocomotionParts[i].DefaultPart)
			{
				Ref->SetSkeletalMesh(LocomotionParts[i].DefaultPart->GetDefaultObject<ULocomotionPart>()->GetSkeletalMeshAsset());
				UClass*						DefaultLocomotionLoaded = LocomotionParts[i].DefaultPart.LoadSynchronous();
				TObjectPtr<ULocomotionPart> LocomotionPartCreated = Cast<ULocomotionPart>(
					GetOwner()->AddComponentByClass(DefaultLocomotionLoaded, false, FTransform::Identity, false));
				if (LocomotionPartCreated)
				{
					LocomotionManagerRef->AddArrayElement(LocomotionPartCreated);
				}
			}
			else if (LocomotionParts[i].PossibleParts)
			{
				int32 Index = FMath::RandRange(0, LocomotionParts[i].PossibleParts->GetPartArray().Num() - 1);

				Ref->SetSkeletalMesh(LocomotionParts[i].PossibleParts->GetPartArray()[Index]->GetSkeletalMeshAsset());
				ULocomotionPart* CastPart = Cast<ULocomotionPart>(LocomotionParts[i].PossibleParts->GetPartArray()[Index]);
				LocomotionManagerRef->AddArrayElement(CastPart);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Oskour"));
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Generated Locomotions for %s"), *this->GetFName().ToString());
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
			else if (PerceptionParts[i].DefaultPart)
			{
				Ref->SetSkeletalMesh(PerceptionParts[i].DefaultPart->GetDefaultObject<UPerceptionPart>()->GetSkeletalMeshAsset());
				UClass*						 DefaultPerceptionLoaded = PerceptionParts[i].DefaultPart.LoadSynchronous();
				TObjectPtr<UPerceptionPart> PerceptionPartCreated = Cast<UPerceptionPart>(
					GetOwner()->AddComponentByClass(DefaultPerceptionLoaded, false, FTransform::Identity, false));
				// if (PerceptionPartCreated)
				//{
				//	PerceptionManagerRef->AddArrayElement(PerceptionPartCreated);
				// }
			}
			else if (PerceptionParts[i].PossibleParts)
			{
				int32 Index = FMath::RandRange(0, PerceptionParts[i].PossibleParts->GetPartArray().Num() - 1);

				Ref->SetSkeletalMesh(PerceptionParts[i].PossibleParts->GetPartArray()[Index]->GetSkeletalMeshAsset());
				UPerceptionPart* CastPart = Cast<UPerceptionPart>(PerceptionParts[i].PossibleParts->GetPartArray()[Index]);
				// if (CastPart)
				//{
				//	PerceptionManagerRef->AddArrayElement(CastPart);
				// }
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Oskour"));
			}
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Generated Perceptions for %s"), *this->GetFName().ToString());
}

FIndividualBodyPart::FIndividualBodyPart()
{
}

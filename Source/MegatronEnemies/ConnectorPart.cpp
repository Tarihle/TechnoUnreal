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

		if (bUseInteraction && InteractionParts.Num() > 0)
		{
			GenerateParts(InteractionParts, EBodyPartType::INTERACTION);
		}
		if (bUseLocomotion && LocomotionParts.Num() > 0)
		{
			GenerateParts(LocomotionParts, EBodyPartType::LOCOMOTION);
		}
		if (bUsePerception && PerceptionParts.Num() > 0)
		{
			GenerateParts(PerceptionParts, EBodyPartType::PERCEPTION);
		}

		LocomotionManagerRef->OnConnectorInitialized();
	}
}

void UConnectorPart::GenerateParts(TArray<FIndividualBodyPart> PartsArray, EBodyPartType PartType)
{
	for (int i = 0; i < PartsArray.Num(); i++)
	{
		USkeletalMeshComponent* Ref = Cast<USkeletalMeshComponent>(PartsArray[i].MeshReference.GetComponent(OwnerCharacter));
		if (!Ref)
		{
			UE_LOG(LogTemp, Error, TEXT("No Ref"));
		}
		else if (PartsArray[i].DefaultPart)
		{
			GenerateDefaultPart(PartsArray, i, PartType, Ref);
		}
		else if (PartsArray[i].PossibleParts)
		{
			GenerateRandomPart(PartsArray, i, PartType, Ref);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("No element in PartsArray"));
		}
	}
}

void UConnectorPart::GenerateDefaultPart(
	TArray<FIndividualBodyPart> PartsArray, int ArrayIndex, EBodyPartType PartType, USkeletalMeshComponent* MeshRef)
{
	UClass* LoadedDefault = PartsArray[ArrayIndex].DefaultPart.LoadSynchronous();

	if (PartType == EBodyPartType::INTERACTION && LoadedDefault)
	{
		MeshRef->SetSkeletalMesh(PartsArray[ArrayIndex].DefaultPart->GetDefaultObject<UInteractionPart>()->GetSkeletalMeshAsset());

		TObjectPtr<UInteractionPart> InteractionPartCreated =
			Cast<UInteractionPart>(GetOwner()->AddComponentByClass(LoadedDefault, false, FTransform::Identity, false));
		InteractionPartCreated->SetHiddenInGame(true);
		InteractionPartCreated->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// if (InteractionPartCreated)
		//{
		//	InteractionManagerRef->AddArrayElement(InteractionPartCreated);
		// }
	}
	else if (PartType == EBodyPartType::LOCOMOTION && LoadedDefault)
	{
		MeshRef->SetSkeletalMesh(PartsArray[ArrayIndex].DefaultPart->GetDefaultObject<ULocomotionPart>()->GetSkeletalMeshAsset());

		TObjectPtr<ULocomotionPart> LocomotionPartCreated =
			Cast<ULocomotionPart>(GetOwner()->AddComponentByClass(LoadedDefault, false, FTransform::Identity, false));

		LocomotionPartCreated->SetHiddenInGame(true);
		LocomotionPartCreated->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		if (LocomotionPartCreated)
		{
			LocomotionManagerRef->AddArrayElement(LocomotionPartCreated);
		}
	}
	else if (PartType == EBodyPartType::PERCEPTION && LoadedDefault)
	{
		MeshRef->SetSkeletalMesh(PartsArray[ArrayIndex].DefaultPart->GetDefaultObject<UPerceptionPart>()->GetSkeletalMeshAsset());

		TObjectPtr<UPerceptionPart> PerceptionPartCreated =
			Cast<UPerceptionPart>(GetOwner()->AddComponentByClass(LoadedDefault, false, FTransform::Identity, false));
		PerceptionPartCreated->SetHiddenInGame(true);
		PerceptionPartCreated->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		// if (PerceptionPartCreated)
		//{
		//	PerceptionManagerRef->AddArrayElement(PerceptionPartCreated);
		// }
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid DefaultPart"));
	}
}

void UConnectorPart::GenerateRandomPart(
	TArray<FIndividualBodyPart> PartsArray, int ArrayIndex, EBodyPartType PartType, USkeletalMeshComponent* MeshRef)
{
	int32 RandIndex = FMath::RandRange(0, PartsArray[ArrayIndex].PossibleParts->GetPartArray().Num() - 1);

	MeshRef->SetSkeletalMesh(PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex]->GetSkeletalMeshAsset());

	if (PartType == EBodyPartType::INTERACTION)
	{
		UInteractionPart* CastPart = Cast<UInteractionPart>(PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex]);
		// if (CastPart)
		//{
		//	InteractionManagerRef->AddArrayElement(CastPart);
		// }
	}
	else if (PartType == EBodyPartType::LOCOMOTION)
	{
		ULocomotionPart* CastPart = Cast<ULocomotionPart>(PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex]);
		if (CastPart)
		{
			LocomotionManagerRef->AddArrayElement(CastPart);
		}
	}
	else if (PartType == EBodyPartType::PERCEPTION)
	{
		UPerceptionPart* CastPart = Cast<UPerceptionPart>(PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex]);
		// if (CastPart)
		//{
		//	PerceptionManagerRef->AddArrayElement(CastPart);
		// }
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Invalid RandomPart"));
	}
}

FIndividualBodyPart::FIndividualBodyPart()
{
}

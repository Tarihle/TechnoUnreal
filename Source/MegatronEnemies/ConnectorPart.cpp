// Fill out your copyright notice in the Description page of Project Settings.

#include "ConnectorPart.h"

#include "InteractionPart.h"
#include "InteractionManager.h"
#include "LocomotionManager.h"
#include "LocomotionPart.h"
#include "MegatronManager.h"
#include "PerceptionManager.h"
#include "PerceptionPart.h"
#include "PossibleBodyParts.h"
#include "GenerationParameters.h"

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
		UMegatronManager* MegatronManager = OwnerCharacter->GetComponentByClass<UMegatronManager>();

		LocomotionManagerRef = MegatronManager->GetLocomotion();
		InteractionManagerRef = MegatronManager->GetInteraction();
		PerceptionManagerRef = MegatronManager->GetPerception();

		if (MegatronManager->GetGenParams())
		{
			WhiteListRef = MegatronManager->GetGenParams()->GetWhiteList();
		}
		// UE_LOG(LogTemp, Warning, TEXT("LocomotionManagerRef set for %s"), *this->GetFName().ToString());

		if (bUseInteraction && InteractionParts.Num() > 0)
		{
			GenerateIndividualPart(InteractionParts, EBodyPartType::INTERACTION);
		}
		if (bUseLocomotion && LocomotionParts.Num() > 0)
		{
			GenerateIndividualPart(LocomotionParts, EBodyPartType::LOCOMOTION);
		}
		if (bUsePerception && PerceptionParts.Num() > 0)
		{
			GenerateIndividualPart(PerceptionParts, EBodyPartType::PERCEPTION);
		}

		LocomotionManagerRef->OnConnectorInitialized();
	}
}

void UConnectorPart::GenerateIndividualPart(TArray<FIndividualBodyPart> PartsArray, EBodyPartType PartType)
{
	for (int ArrayIndex = 0; ArrayIndex < PartsArray.Num(); ArrayIndex++)
	{
		USkeletalMeshComponent* Ref =
			Cast<USkeletalMeshComponent>(PartsArray[ArrayIndex].MeshReference.GetComponent(OwnerCharacter));
		if (!Ref || (!PartsArray[ArrayIndex].DefaultPart && !PartsArray[ArrayIndex].PossibleParts))
		{
			UE_LOG(LogTemp, Error, TEXT("No Ref or no element in PartsArray"));
			return;
		}

		UClass* LoadedPart;

		if (PartsArray[ArrayIndex].DefaultPart)
		{
			LoadedPart = PartsArray[ArrayIndex].DefaultPart.LoadSynchronous();
		}
		else
		{
			int32 RandIndex = FMath::RandRange(0, PartsArray[ArrayIndex].PossibleParts->GetPartArray().Num() - 1);
			LoadedPart = PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex].LoadSynchronous();
		}

		bool  PartUsed = false;
		int32 RandWeight = 99;

		for (int i = 0; i < WhiteListRef.Num(); i++)
		{
			if (WhiteListRef[i].GetConditionFilledState() && WhiteListRef[i].GetReactorBodyPartType() == PartType)
			{
				for (int j = 0; j < PartsArray[ArrayIndex].PossibleParts->GetPartArray().Num(); j++)
				{
					if (WhiteListRef[i].Reactor->GetDefaultObject() ==
						PartsArray[ArrayIndex].PossibleParts->GetPartArray()[j]->GetDefaultObject())
					{
						int32 oui = FMath::RandRange(0, RandWeight);
						if (oui < WhiteListRef[i].Weight)
						{
							PartUsed = true;
							LoadedPart = PartsArray[ArrayIndex].PossibleParts->GetPartArray()[j].LoadSynchronous();
						}
						else
						{
							RandWeight -= WhiteListRef[i].Weight;
						}
						break;
					}
				}

				if (PartUsed)
				{
					break;
				}
			}
		}

		if (LoadedPart && PartType == EBodyPartType::INTERACTION)
		{
			Ref->SetSkeletalMesh(LoadedPart->GetDefaultObject<UInteractionPart>()->GetSkeletalMeshAsset());

			TObjectPtr<UInteractionPart> InteractionPartCreated =
				Cast<UInteractionPart>(GetOwner()->AddComponentByClass(LoadedPart, false, FTransform::Identity, false));
			InteractionPartCreated->SetHiddenInGame(true);
			InteractionPartCreated->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			if (InteractionPartCreated)
			{
				InteractionManagerRef->AddArrayElement(InteractionPartCreated);
			}
		}
		else if (PartType == EBodyPartType::LOCOMOTION)
		{
			Ref->SetSkeletalMesh(LoadedPart->GetDefaultObject<ULocomotionPart>()->GetSkeletalMeshAsset());

			TObjectPtr<ULocomotionPart> LocomotionPartCreated =
				Cast<ULocomotionPart>(GetOwner()->AddComponentByClass(LoadedPart, false, FTransform::Identity, false));
			LocomotionPartCreated->SetHiddenInGame(true);
			LocomotionPartCreated->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			if (LocomotionPartCreated)
			{
				LocomotionManagerRef->AddArrayElement(LocomotionPartCreated);
			}
		}
		else if (PartType == EBodyPartType::PERCEPTION)
		{
			Ref->SetSkeletalMesh(LoadedPart->GetDefaultObject<UPerceptionPart>()->GetSkeletalMeshAsset());

			TObjectPtr<UPerceptionPart> PerceptionPartCreated =
				Cast<UPerceptionPart>(GetOwner()->AddComponentByClass(LoadedPart, false, FTransform::Identity, false));
			PerceptionPartCreated->SetHiddenInGame(true);
			PerceptionPartCreated->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			if (PerceptionPartCreated)
			{
				PerceptionManagerRef->AddArrayElement(PerceptionPartCreated);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Invalid Part"));
			return;
		}

		for (int k = 0; k < WhiteListRef.Num(); k++)
		{
			if (LoadedPart->StaticClass() == WhiteListRef[k].Condition->StaticClass())
			{
				WhiteListRef[k].SetConditionFilledState(true);
			}
		}
	}
}

FIndividualBodyPart::FIndividualBodyPart()
{
}

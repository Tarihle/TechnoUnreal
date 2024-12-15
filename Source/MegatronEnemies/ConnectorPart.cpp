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

		if (UGenerationParameters* GenParams = MegatronManager->GetGenParams())
		{
			WhiteListRef = GenParams->GetWhiteList();
			BlackListRef = GenParams->GetBlackList();
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

void UConnectorPart::EndPlay(EEndPlayReason::Type Reason)
{
	Super::EndPlay(Reason);

	if (bUseInteraction && InteractionParts.Num() > 0)
	{
		ReinitPossibleParts(InteractionParts);
	}
	if (bUseLocomotion && LocomotionParts.Num() > 0)
	{
		ReinitPossibleParts(LocomotionParts);
	}
	if (bUsePerception && PerceptionParts.Num() > 0)
	{
		ReinitPossibleParts(PerceptionParts);
	}
}

void UConnectorPart::GenerateIndividualPart(TArray<FIndividualBodyPart> PartsArray, EBodyPartType PartType)
{
	for (int ArrayIndex = 0; ArrayIndex < PartsArray.Num(); ArrayIndex++)
	{
		USkeletalMeshComponent* Ref =
			Cast<USkeletalMeshComponent>(PartsArray[ArrayIndex].MeshReference.GetComponent(OwnerCharacter));
		if (!Ref || !(PartsArray[ArrayIndex].DefaultPart || PartsArray[ArrayIndex].PossibleParts))
		{
			UE_LOG(LogTemp, Error, TEXT("No Ref or no element in PartsArray"));
			return;
		}

		UClass*	   LoadedPartClass;
		UBodyPart* LoadedPart;

		if (PartsArray[ArrayIndex].DefaultPart)
		{
			LoadedPartClass = PartsArray[ArrayIndex].DefaultPart->StaticClass();
			LoadedPart = dynamic_cast<UBodyPart*>(
				OwnerCharacter->AddComponentByClass(PartsArray[ArrayIndex].DefaultPart, false, OwnerCharacter->GetTransform(), false));
			UE_LOG(LogTemp, Display, TEXT("%s"), *PartsArray[ArrayIndex].DefaultPart.GetDefaultObject()->GetFName().ToString());
		}
		else
		{
			int32 RandIndex = FMath::RandRange(0, PartsArray[ArrayIndex].PossibleParts->GetPartArray().Num() - 1);
			LoadedPartClass = PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex]->StaticClass();
			LoadedPart = dynamic_cast<UBodyPart*>(
				OwnerCharacter->AddComponentByClass(PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex],
					false, OwnerCharacter->GetTransform(), false));
			bool  PartUsed = false;
			int32 RandWeight = 99;

			for (int i = 0; i < WhiteListRef.Num(); i++)
			{
				if (!WhiteListRef[i].GetConditionFilledState())
				{
					continue;
				}
				for (int ReactorIndex = 0; ReactorIndex < WhiteListRef[i].ReactorList.Num(); ReactorIndex++)
				{
					if (WhiteListRef[i].GetReactorBodyPartType(ReactorIndex) != PartType)
					{
						continue;
					}
					for (int j = 0; j < PartsArray[ArrayIndex].PossibleParts->GetArraySize(); j++)
					{
						if (WhiteListRef[i].ReactorList[ReactorIndex].Reactor->GetDefaultObject() ==
							PartsArray[ArrayIndex].PossibleParts->GetPartArray()[j].GetDefaultObject())
						{
							int32 oui = FMath::RandRange(0, RandWeight);
							if (oui < WhiteListRef[i].GetReactorWeight(ReactorIndex))
							{
								LoadedPartClass = PartsArray[ArrayIndex].PossibleParts->GetPartArray()[j]->StaticClass();
								LoadedPart = dynamic_cast<UBodyPart*>(
								OwnerCharacter->AddComponentByClass(PartsArray[ArrayIndex].PossibleParts->GetPartArray()[j],
									false, OwnerCharacter->GetTransform(), false));
								UE_LOG(LogTemp, Display, TEXT("Using %s from WhiteList."), *LoadedPart->GetFName().ToString());
							}
							else
							{
								RandWeight -= WhiteListRef[i].GetReactorWeight(ReactorIndex);
							}
							goto SetMeshes;
						}
					}
				}
			}
		}

	SetMeshes:

		if (LoadedPartClass && PartType == EBodyPartType::INTERACTION)
		{
			TObjectPtr<UInteractionPart> InteractionPartCreated = Cast<UInteractionPart>(LoadedPart);

			Ref->SetSkeletalMesh(InteractionPartCreated->GetSkeletalMeshAsset());
			InteractionPartCreated->SetHiddenInGame(true);
			InteractionPartCreated->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			InteractionPartCreated->RefMeshComponent = Ref;
			if (InteractionPartCreated)
			{
				InteractionManagerRef->AddArrayElement(InteractionPartCreated);
			}
		}
		else if (LoadedPartClass && PartType == EBodyPartType::LOCOMOTION)
		{
			TObjectPtr<ULocomotionPart> LocomotionPartCreated = Cast<ULocomotionPart>(LoadedPart);

			Ref->SetSkeletalMesh(LocomotionPartCreated->GetSkeletalMeshAsset());
			LocomotionPartCreated->SetHiddenInGame(true);
			LocomotionPartCreated->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			LocomotionPartCreated->RefMeshComponent = Ref;
			if (LocomotionPartCreated)
			{
				LocomotionManagerRef->AddArrayElement(LocomotionPartCreated);
			}
		}
		else if (LoadedPartClass && PartType == EBodyPartType::PERCEPTION)
		{
			TObjectPtr<UPerceptionPart> PerceptionPartCreated = Cast<UPerceptionPart>(LoadedPart);

			Ref->SetSkeletalMesh(PerceptionPartCreated->GetSkeletalMeshAsset());
			PerceptionPartCreated->SetHiddenInGame(true);
			PerceptionPartCreated->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			PerceptionPartCreated->RefMeshComponent = Ref;
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

		ValidateListsCondition(LoadedPart);
	}
}

void UConnectorPart::ReinitPossibleParts(TArray<FIndividualBodyPart> PartsArray)
{
	for (FIndividualBodyPart Part : PartsArray)
	{
		if (Part.PossibleParts)
		{
			Part.PossibleParts->ReinitArraySize();
		}
	}
}

void UConnectorPart::RemoveBlackListedParts(int ArrayIndex)
{
	for (TSubclassOf<UBodyPart> BodyPart : BlackListRef[ArrayIndex].Reactions)
	{
		if (!BodyPart)
		{
			continue;
		}
		if (UBodyPart::IsInteraction(BodyPart))
		{
			for (FIndividualBodyPart Interaction : InteractionParts)
			{
				if (Interaction.PossibleParts && Interaction.PossibleParts->RemoveByName(BodyPart))
				{
					UE_LOG(LogTemp, Warning, TEXT("Successfully removed %s from InteractionParts"), *BodyPart->GetFName().ToString());
				}
			}
		}
		else if (UBodyPart::IsLocomotion(BodyPart))
		{
			for (FIndividualBodyPart Locomotion : LocomotionParts)
			{
				if (Locomotion.PossibleParts && Locomotion.PossibleParts->RemoveByName(BodyPart))
				{
					UE_LOG(
						LogTemp, Warning, TEXT("Successfully removed %s from LocomotionParts"), *BodyPart->GetFName().ToString());
				}
			}
		}
		else if (UBodyPart::IsPerception(BodyPart))
		{
			for (FIndividualBodyPart Perception : PerceptionParts)
			{
				if (Perception.PossibleParts && Perception.PossibleParts->RemoveByName(BodyPart))
				{
					UE_LOG(
						LogTemp, Warning, TEXT("Successfully removed %s from PerceptionParts"), *BodyPart->GetFName().ToString());
				}
			}
		}
	}
}

void UConnectorPart::ValidateListsCondition(UBodyPart* LoadedPart)
{
	for (int k = 0; k < WhiteListRef.Num(); k++)
	{
		if (LoadedPart->GetFName() == WhiteListRef[k].Condition->GetDefaultObject()->GetFName() &&
			!WhiteListRef[k].GetConditionFilledState())
		{
			WhiteListRef[k].SetConditionFilledState(true);
			UE_LOG(
				LogTemp, Display, TEXT("Validating condition in generation parameters for %s (whitelist)."),
				*LoadedPart->GetFName().ToString());
		}
	}

	for (int l = 0; l < BlackListRef.Num(); l++)
	{
		if (LoadedPart->GetFName() == BlackListRef[l].Condition->GetDefaultObject()->GetFName() &&
			!BlackListRef[l].GetConditionFilledState())
		{
			RemoveBlackListedParts(l);
			BlackListRef[l].SetConditionFilledState(true);
			UE_LOG(
				LogTemp, Display, TEXT("Validating condition in generation parameters for %s (blacklist)."),
				*LoadedPart->GetFName().ToString());
		}
	}
}

FIndividualBodyPart::FIndividualBodyPart()
{
}

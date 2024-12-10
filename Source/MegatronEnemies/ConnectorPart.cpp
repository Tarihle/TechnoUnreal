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
			LoadedPart = PartsArray[ArrayIndex].DefaultPart.GetDefaultObject();
			UE_LOG(LogTemp, Display, TEXT("Using %s from default."), *LoadedPart->GetFName().ToString());
		}
		else
		{
			int32 RandIndex = FMath::RandRange(0, PartsArray[ArrayIndex].PossibleParts->GetPartArray().Num() - 1);
			LoadedPartClass = PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex]->StaticClass();
			LoadedPart = PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex].GetDefaultObject();
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
					for (int j = 0; j < PartsArray[ArrayIndex].PossibleParts->GetPartArray().Num(); j++)
					{
						if (WhiteListRef[i].ReactorList[ReactorIndex].Reactor->GetDefaultObject() ==
							PartsArray[ArrayIndex].PossibleParts->GetPartArray()[j].GetDefaultObject())
						{
							int32 oui = FMath::RandRange(0, RandWeight);
							if (oui < WhiteListRef[i].GetReactorWeight(ReactorIndex))
							{
								LoadedPartClass = PartsArray[ArrayIndex].PossibleParts->GetPartArray()[j]->StaticClass();
								LoadedPart = PartsArray[ArrayIndex].PossibleParts->GetPartArray()[j].GetDefaultObject();
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
			//UE_LOG(
			//	LogTemp, Warning, TEXT("LoadedPartClass: %s, ConditionClass: %s"),
			//	*LoadedPart->GetFName().ToString(),
			//	*WhiteListRef[k].Condition->GetDefaultObject()->GetFName().ToString());

			if (LoadedPart->GetFName() == WhiteListRef[k].Condition->GetDefaultObject()->GetFName() &&
				!WhiteListRef[k].GetConditionFilledState())
			{
				WhiteListRef[k].SetConditionFilledState(true);
				UE_LOG(
					LogTemp, Display, TEXT("Validating condition in generation parameters for %s."),
					*LoadedPart->GetFName().ToString());
			}
		}
	}
}

FIndividualBodyPart::FIndividualBodyPart()
{
}

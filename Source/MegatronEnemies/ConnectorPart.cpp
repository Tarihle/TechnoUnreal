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

unsigned int Usage = 0b0;

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

		unsigned int TotalPartNumber = 0;

		if (bUseInteraction && InteractionParts.Num() > 0)
		{
			Usage += USEINTERACTION;
			TotalPartNumber += InteractionParts.Num();
		}
		if (bUseLocomotion && LocomotionParts.Num() > 0)
		{
			Usage += USELOCOMOTION;
			TotalPartNumber += LocomotionParts.Num();
		}
		if (bUsePerception && PerceptionParts.Num() > 0)
		{
			Usage += USEPERCEPTION;
			TotalPartNumber += PerceptionParts.Num();
		}

		for (unsigned int i = 0; i < TotalPartNumber; i++)
		{
			if (Usage == 0b000)
			{
				break;
			}
			int32 RGN = -1;
			switch (Usage)
			{
			case 0b111:
				RGN = FMath::RandRange(0, 2);
				break;
			case 0b001:
				RGN = 0;
				break;
			case 0b010:
				RGN = 1;
				break;
			case 0b100:
				RGN = 2;
				break;
			case 0b011:
				RGN = FMath::RandRange(0, 1);
				break;
			case 0b110:
				RGN = FMath::RandRange(1, 2);
				break;
			case 0b101:
				int temp = FMath::RandRange(0, 3);
				temp = temp % 2;
				if (temp == 1)
				{
					temp += 1;
				}
				RGN = temp;
				break;
			}

			switch (RGN)
			{
			case 0:
				GenerateIndividualPart(InteractionParts, EBodyPartType::INTERACTION, InteractionArrayIndex);
				if (InteractionArrayIndex == InteractionParts.Num())
				{
					Usage -= USEINTERACTION;
				}
				break;
			case 1:
				GenerateIndividualPart(LocomotionParts, EBodyPartType::LOCOMOTION, LocomotionArrayIndex);
				if (LocomotionArrayIndex == LocomotionParts.Num())
				{
					Usage -= USELOCOMOTION;
				}
				break;
			case 2:
				GenerateIndividualPart(PerceptionParts, EBodyPartType::PERCEPTION, PerceptionArrayIndex);
				if (PerceptionArrayIndex == PerceptionParts.Num())
				{
					Usage -= USEPERCEPTION;
				}
				break;
			}
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

void UConnectorPart::GenerateIndividualPart(TArray<FIndividualBodyPart> PartsArray, EBodyPartType PartType, int& ArrayIndex)
{
	if (!(PartsArray[ArrayIndex].DefaultPart || PartsArray[ArrayIndex].PossibleParts))
	{
		UE_LOG(LogTemp, Error, TEXT("No Ref or no element in PartsArray"));
		return;
	}

	UBodyPart* LoadedPart;

	if (PartsArray[ArrayIndex].DefaultPart)
	{
		LoadedPart = dynamic_cast<UBodyPart*>(
			OwnerCharacter->AddComponentByClass(PartsArray[ArrayIndex].DefaultPart, false, this->GetRelativeTransform(), false));
		UE_LOG(LogTemp, Display, TEXT("%s"), *PartsArray[ArrayIndex].DefaultPart.GetDefaultObject()->GetFName().ToString());
	}
	else
	{
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
							LoadedPart = dynamic_cast<UBodyPart*>(OwnerCharacter->AddComponentByClass(
								PartsArray[ArrayIndex].PossibleParts->GetPartArray()[j], false, this->GetRelativeTransform(),
								false));
							UE_LOG(LogTemp, Display, TEXT("Using %s from WhiteList."), *LoadedPart->GetFName().ToString());
							SetMeshes(LoadedPart, PartType);
							++ArrayIndex;
							return;
						}
						else
						{
							RandWeight -= WhiteListRef[i].GetReactorWeight(ReactorIndex);
						}
					}
				}
			}
		}

		int32 RandIndex = FMath::RandRange(0, PartsArray[ArrayIndex].PossibleParts->GetPartArray().Num() - 1);
		LoadedPart = dynamic_cast<UBodyPart*>(OwnerCharacter->AddComponentByClass(
			PartsArray[ArrayIndex].PossibleParts->GetPartArray()[RandIndex], false, this->GetRelativeTransform(), false));
	}

	SetMeshes(LoadedPart, PartType);
	++ArrayIndex;
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
					UE_LOG(
						LogTemp, Warning, TEXT("Successfully removed %s from InteractionParts"), *BodyPart->GetFName().ToString());
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
		if (LoadedPart->GetClass()->GetDefaultObject()->GetFName() == WhiteListRef[k].Condition->GetDefaultObject()->GetFName() &&
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
		if (LoadedPart->GetClass()->GetDefaultObject()->GetFName() == BlackListRef[l].Condition->GetDefaultObject()->GetFName() &&
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

void UConnectorPart::SetMeshes(UBodyPart* LoadedPart, EBodyPartType PartType)
{
	if (LoadedPart && PartType == EBodyPartType::INTERACTION)
	{
		TObjectPtr<UInteractionPart> InteractionPartCreated = Cast<UInteractionPart>(LoadedPart);

		InteractionPartCreated->SetLeaderPoseComponent(this);
		if (InteractionPartCreated)
		{
			InteractionManagerRef->AddArrayElement(InteractionPartCreated);
		}
	}
	else if (LoadedPart && PartType == EBodyPartType::LOCOMOTION)
	{
		TObjectPtr<ULocomotionPart> LocomotionPartCreated = Cast<ULocomotionPart>(LoadedPart);

		LocomotionPartCreated->SetLeaderPoseComponent(this);
		if (LocomotionPartCreated)
		{
			LocomotionManagerRef->AddArrayElement(LocomotionPartCreated);
		}
	}
	else if (LoadedPart && PartType == EBodyPartType::PERCEPTION)
	{
		TObjectPtr<UPerceptionPart> PerceptionPartCreated = Cast<UPerceptionPart>(LoadedPart);

		PerceptionPartCreated->SetLeaderPoseComponent(this);
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

FIndividualBodyPart::FIndividualBodyPart()
{
}

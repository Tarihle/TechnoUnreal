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

	if (CharacterOwnerRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("CharacterOwnerRef"));
		if (bUseInteraction && InteractionParts.Num() > 0)
		{
			UE_LOG(LogTemp, Warning, TEXT("%d"), InteractionParts.Num());
			if (InteractionParts[0])
			{
				UE_LOG(LogTemp, Warning, TEXT("0"));
				UBodyPart* CastPart = Cast<UBodyPart>(InteractionParts[0]);
				USkeletalMeshComponent* Ref = Cast<USkeletalMeshComponent>(CastPart->MeshReference.GetComponent(CharacterOwnerRef));

				if (Ref)
				{
					UE_LOG(LogTemp, Warning, TEXT("Ref"));
					Ref->SetSkeletalMesh(CastPart->SkeletalMesh);
				}
			}
			//UE_LOG(LogTemp, Warning, TEXT("%s"), *Body.GetName());
		}
		//else if (PossibleBodies)
		//{
		//	int32 Index = FMath::RandRange(0, PossibleBodies->GetPartArray().Num() - 1);
		//	UE_LOG(LogTemp, Warning, TEXT("PossibleBodies: %d"), Index);
		//	Ref->SetSkeletalMesh(PossibleBodies->GetPartArray()[Index]->SkeletalMesh);
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Error, TEXT("Oskour"));
		//}
	}
}

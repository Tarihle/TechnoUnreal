// Fill out your copyright notice in the Description page of Project Settings.

#include "PerceptionPart.h"

#include "PerceptionManager.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Touch.h"

void UPerceptionPart::InitializeComponent()
{
	Super::InitializeComponent();

	if (APawn* PawnOwner = Cast<APawn>(GetOwner()))
	{
		UActorComponent* Component = PawnOwner->Controller->GetComponentByClass(UAIPerceptionComponent::StaticClass());
		PerceptionComponent = dynamic_cast<UAIPerceptionComponent*>(Component);
	}

	checkf(PerceptionComponent, TEXT("No AI Perception Component found in owner pawn"));
}

bool UPerceptionPart::IsSenseEnabled(EPerceptionID Sense) const
{
	switch (Sense)
	{
	case EPerceptionID::SIGHT:
		return Constraints.bCanSee;

	case EPerceptionID::HEARING:
		return Constraints.bCanHear;

	case EPerceptionID::TOUCH:
		return Constraints.bCanFeelTouch;

	default:
		return false;
	}
}

void UPerceptionPart::EnableSight()
{
	SetSenseEnabled(EPerceptionID::SIGHT, true);
}

void UPerceptionPart::DisableSight()
{
	SetSenseEnabled(EPerceptionID::SIGHT, false);
}

void UPerceptionPart::EnableHearing()
{
	SetSenseEnabled(EPerceptionID::HEARING, true);
}

void UPerceptionPart::DisableHearing()
{
	SetSenseEnabled(EPerceptionID::HEARING, false);
}

void UPerceptionPart::EnableTouch()
{
	SetSenseEnabled(EPerceptionID::TOUCH, true);
}

void UPerceptionPart::DisableTouch()
{
	SetSenseEnabled(EPerceptionID::TOUCH, false);
}

TArray<AActor*> UPerceptionPart::GetAllPerceivedActors() const
{
	return GetSensedActors(nullptr);
}

TArray<class AActor*> UPerceptionPart::GetHeardActors() const
{
	return GetSensedActors(UAISense_Hearing::StaticClass());
}

TArray<class AActor*> UPerceptionPart::GetSeenActors() const
{
	return GetSensedActors(UAISense_Sight::StaticClass());
}

TArray<class AActor*> UPerceptionPart::GetTouchedActors() const
{
	return GetSensedActors(UAISense_Touch::StaticClass());
}

void UPerceptionPart::SetSenseEnabled(EPerceptionID Sense, bool bEnabled)
{
	switch (Sense)
	{
	case EPerceptionID::SIGHT:
		Constraints.bCanSee = bEnabled;
		PerceptionComponent->SetSenseEnabled(UAISense_Sight::StaticClass(), bEnabled);
		break;

	case EPerceptionID::HEARING:
		Constraints.bCanHear = bEnabled;
		PerceptionComponent->SetSenseEnabled(UAISense_Hearing::StaticClass(), bEnabled);
		break;

	case EPerceptionID::TOUCH:
		Constraints.bCanFeelTouch = bEnabled;
		PerceptionComponent->SetSenseEnabled(UAISense_Touch::StaticClass(), bEnabled);
		break;

	default:
		break;
	}
}

void UPerceptionPart::BeginPlay()
{
	Super::BeginPlay();

	/* In UE 5.4, UpdateListener is only called if the PerceptionComponent has sense configs in
	 its array right after construction. This might not be the case if all configs are stored
	 in perception parts, so we update it manually to have a valid Listener ID */
	UAIPerceptionSystem* AIPerceptionSys = UAIPerceptionSystem::GetCurrent(GetWorld());
	if (PerceptionComponent->GetListenerId() == FPerceptionListenerID::InvalidID())
	{
		AIPerceptionSys->UpdateListener(*PerceptionComponent);
	}

	for (TObjectPtr<UAISenseConfig>& Config : Senses)
	{
		if (Config)
			PerceptionComponent->ConfigureSense(*Config);
	}

	/*
	 * This is called after UAIPerceptionComponent::RegisterSenseConfig when said component
	 * has configs in its array at construction. Is it okay ? We'll see :)
	 */
	AIPerceptionSys->UpdateListener(*PerceptionComponent);
}

TArray<class AActor*> UPerceptionPart::GetSensedActors(const TSubclassOf<class UAISense>& Sense) const
{
	TArray<AActor*> Perceived;

	PerceptionComponent->GetKnownPerceivedActors(Sense, Perceived);

	return Perceived;
}

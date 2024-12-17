// Fill out your copyright notice in the Description page of Project Settings.

#include "MegatronManager.h"

#include "InteractionManager.h"
#include "LocomotionManager.h"
#include "PerceptionManager.h"
#include "Public/HealthSystem.h"

#include "Components/WidgetComponent.h"

// Sets default values for this component's properties
UMegatronManager::UMegatronManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	LocomotionManager = CreateDefaultSubobject<ULocomotionManager>(TEXT("LocomotionManager"));
	InteractionManager = CreateDefaultSubobject<UInteractionManager>(TEXT("InteractionManager"));
	PerceptionManager = CreateDefaultSubobject<UPerceptionManager>(TEXT("PerceptionManager"));

	HealthSystem = CreateDefaultSubobject<UHealthSystem>(TEXT("HealthSystem"));
	HealthWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthWidget"));
	if (HealthWidget)
	{
		HealthWidget->SetWidgetSpace(EWidgetSpace::World);
		HealthWidget->SetVisibility(true);
		//HealthWidget->RegisterComponent();
	}
}

// Called when the game starts
void UMegatronManager::BeginPlay()
{
	Super::BeginPlay();
	LocomotionManager->SetConnectorCount(Connectors.Num());
	//if (GetOwner()->StaticClass() != this->StaticClass())
	//{
	//	GetOwner()->AddOwnedComponent(HealthWidget);
	//}
}

// Called every frame
void UMegatronManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

ULocomotionManager* UMegatronManager::GetLocomotion()
{
	return LocomotionManager;
}

UInteractionManager* UMegatronManager::GetInteraction()
{
	return InteractionManager;
}

UPerceptionManager* UMegatronManager::GetPerception()
{
	return PerceptionManager;
}

UGenerationParameters* UMegatronManager::GetGenParams()
{
	return GenerationParameters;
}

void UMegatronManager::ClearOnScreenDebugMessages()
{
	if (GEngine)
	{
		GEngine->ClearOnScreenDebugMessages();
	}
}

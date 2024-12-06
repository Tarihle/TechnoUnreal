// Fill out your copyright notice in the Description page of Project Settings.

#include "MegatronEnemies/Public/HealthSystem.h"

// Sets default values for this component's properties
UHealthSystem::UHealthSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UHealthSystem::BeginPlay()
{
	Super::BeginPlay();

	if (Health == 0)
		Health = MaxHealth;
}

// Called every frame
void UHealthSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthSystem::SetHealth(double const NewHealth)
{
	Health = FMath::Clamp(NewHealth, 0.0, GetMaxHealth());

	OnHealthChanged.Broadcast(GetHealth());

	if (IsDead())
		OnDeath.Broadcast();
}

/*void UHealthSystem::TakeDamage(double DamageTaken, AActor* DamageSource)
{
	SetHealth(FMath::Clamp(GetHealth() - DamageTaken, 0.0f, GetMaxHealth()));
	OnHealthChanged.Broadcast(GetHealth());
	if (IsDead()) OnDeath.Broadcast();
}*/

void UHealthSystem::SetMaxHealth(double const NewMaxHealth)
{
	MaxHealth = NewMaxHealth;

	OnMaxHealthChanged.Broadcast(GetMaxHealth());
}

void UHealthSystem::Heal(double HealAmount, AActor* HealSource)
{
	SetHealth(FMath::Clamp(GetHealth() + HealAmount, 0.0f, GetMaxHealth()));
	OnHealthChanged.Broadcast(GetHealth());
}

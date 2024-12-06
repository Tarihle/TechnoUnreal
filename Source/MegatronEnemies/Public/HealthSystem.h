// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, double, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChange, double, MaxHealth);

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MEGATRONENEMIES_API UHealthSystem : public UActorComponent
{
	GENERATED_BODY()

  public:
	// Sets default values for this component's properties
	UHealthSystem();

  protected:
	// Called when the game starts
	virtual void BeginPlay() override;

  public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintGetter)
	double GetHealth() const
	{
		return Health;
	}

	UFUNCTION(BlueprintSetter)
	void SetHealth(double const NewHealth);

	UFUNCTION(BlueprintGetter)
	double GetMaxHealth() const
	{
		return MaxHealth;
	}

	UFUNCTION(BlueprintSetter)
	void SetMaxHealth(double const NewMaxHealth);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = Health)
	bool IsDead() const
	{
		return Health <= 0;
	}

	// UFUNCTION(BlueprintCallable, Category="Health")
	// void TakeDamage(double DamageTaken, AActor* DamageSource);

	UFUNCTION(BlueprintCallable, Category = Health)
	void Heal(double HealAmount, AActor* HealSource = nullptr);

  private:
	UPROPERTY(EditAnywhere, BlueprintGetter = GetHealth, BlueprintSetter = SetHealth, Category = Parameters)
	double Health;

	UPROPERTY(
		EditAnywhere, BlueprintGetter = GetMaxHealth, BlueprintSetter = SetMaxHealth, meta = (ExposeOnSpawn),
		Category = Parameters)
	double MaxHealth = 100.0f;

  public:
	UPROPERTY(BlueprintAssignable, Category = Health)
	FOnDeath OnDeath;

	UPROPERTY(BlueprintAssignable, Category = Health)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable, Category = MaxHealth)
	FOnMaxHealthChange OnMaxHealthChanged;
};

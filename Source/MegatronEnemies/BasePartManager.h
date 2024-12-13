// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BodyPart.h"
#include "Components/ActorComponent.h"
#include "Templates/UnrealTypeTraits.h"

#include "BasePartManager.generated.h"


#define BASE_PART_TEMPLATE template <typename TPartType UE_REQUIRES(TIsDerivedFrom<TPartType, UBodyPart>::Value)> inline


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UBasePartManager : public UActorComponent
{
	GENERATED_BODY()

public:
	
	void AddArrayElement(UBodyPart* const ChosenElement);
	void OnPartDestroyed(UBodyPart* Part);
	
protected:
	 
	BASE_PART_TEMPLATE
	TPartType* GetRandomPartBase();

	BASE_PART_TEMPLATE
	TArray<TPartType*> GetAllPartsWithTaskByClassBase(const TSubclassOf<class UMegatronTask>& TaskClass);

	BASE_PART_TEMPLATE
	TArray<TPartType*> GetAllPartsWithTaskByTagBase(const struct FGameplayTag& Tag);

protected:
	
	UPROPERTY()
	TObjectPtr<class ACharacter>   OwnerCharacter;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TArray<UBodyPart*>			    SelectedBodyParts;
};



// Template implementations


BASE_PART_TEMPLATE TPartType* UBasePartManager::GetRandomPartBase()
{
	if (SelectedBodyParts.IsEmpty())
		return nullptr;

	return dynamic_cast<TPartType*>(SelectedBodyParts[FMath::RandRange(0, SelectedBodyParts.Num() - 1)]);
}

BASE_PART_TEMPLATE
TArray<TPartType*> UBasePartManager::GetAllPartsWithTaskByClassBase(const TSubclassOf<class UMegatronTask>&  TaskClass)
{
	if (SelectedBodyParts.IsEmpty())
		return TArray<TPartType*>();

	TArray<TPartType*> FilteredArray;

	for (UBodyPart* Part : SelectedBodyParts)
	{
		if (Part->HasTaskByClass(TaskClass))
			FilteredArray.Add(dynamic_cast<TPartType*>(Part));
	}

	return FilteredArray;
}


BASE_PART_TEMPLATE
TArray<TPartType*> UBasePartManager::GetAllPartsWithTaskByTagBase(const struct FGameplayTag& Tag)
{
	if (SelectedBodyParts.IsEmpty())
		return TArray<TPartType*>();

	TArray<TPartType*> FilteredArray;

	for (UBodyPart* Part : SelectedBodyParts)
	{
		if (Part->HasTaskByTag(Tag))
			FilteredArray.Add(dynamic_cast<TPartType*>(Part));
	}

	return FilteredArray;
}

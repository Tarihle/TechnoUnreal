// Fill out your copyright notice in the Description page of Project Settings.

#include "PossibleBodyParts.h"

#include "BodyPart.h"

UPossibleBodyParts::UPossibleBodyParts()
{
}

void UPossibleBodyParts::PostLoad()
{
	Super::PostLoad();

	TrueSize = BodyPartsArray.Num();
	UE_LOG(LogTemp, Warning, TEXT("PostLoad PossibleBodyParts %d"), TrueSize);
}

TArray<TSubclassOf<UBodyPart>> UPossibleBodyParts::GetPartArray()
{
	return BodyPartsArray;
}

bool UPossibleBodyParts::RemoveByName(TSubclassOf<UBodyPart> Part)
{
	for (int i = 0; i < TrueSize; i++)
	{
		if (Part->GetFName() == BodyPartsArray[i]->GetFName() && TrueSize > 0)
		{
			if (i != TrueSize - 1)
			{
				BodyPartsArray.Swap(i, TrueSize - 1);
			}

			TrueSize -= 1;
			return true;
		}
	}
	return false;
}

int UPossibleBodyParts::GetArraySize()
{
	return TrueSize;
}

void UPossibleBodyParts::ReinitArraySize()
{
	TrueSize = BodyPartsArray.Num();
}

int UPossibleBodyParts::ContainsByName(TSubclassOf<UBodyPart> Part)
{
	for (int i = 0; i < TrueSize; i++)
	{
		if (Part->GetFName() == BodyPartsArray[i]->GetFName())
		{
			return i;
		}
	}
	return -1;
}

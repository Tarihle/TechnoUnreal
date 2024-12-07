// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePartManager.h"

void UBasePartManager::AddArrayElement(UBodyPart* const ChosenElement)
{
	SelectedBodyParts.Add(ChosenElement);
}

void UBasePartManager::OnPartDestroyed(UBodyPart* Part)
{
	SelectedBodyParts.Remove(Part);
}


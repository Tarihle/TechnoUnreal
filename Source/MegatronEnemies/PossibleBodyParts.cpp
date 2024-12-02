// Fill out your copyright notice in the Description page of Project Settings.


#include "PossibleBodyParts.h"
#include "BodyPart.h"

UPossibleBodyParts::UPossibleBodyParts()
{
}

TArray<UBodyPart*> UPossibleBodyParts::GetPartArray()
{
    return BodyPartsArray;
}

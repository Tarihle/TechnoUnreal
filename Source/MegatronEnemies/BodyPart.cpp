// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyPart.h"

UBodyPart::UBodyPart()
{
}


bool UBodyPart::IsLocomotion(UBodyPart* Part)
{
	return Part->Type == EBodyPartType::LOCOMOTION;
}

bool UBodyPart::IsConnector(UBodyPart* Part)
{
	return Part->Type == EBodyPartType::CONNECTOR;
}

bool UBodyPart::IsInteraction(UBodyPart* Part)
{
	return Part->Type == EBodyPartType::INTERACTION;
}

bool UBodyPart::IsPerception(UBodyPart* Part)
{
	return Part->Type == EBodyPartType::PERCEPTION;
}
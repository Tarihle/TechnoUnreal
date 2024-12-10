// Fill out your copyright notice in the Description page of Project Settings.

#include "GenerationParameters.h"

// #include "../BodyPart.h"

UGenerationParameters::UGenerationParameters()
{
}

TArray<FWeightedParam> UGenerationParameters::GetWhiteList()
{
	return WhiteList;
}

FWeightedParam::FWeightedParam()
{
}

bool FWeightedParam::GetConditionFilledState()
{
	return ConditionFilled;
}

void FWeightedParam::SetConditionFilledState(bool State)
{
	ConditionFilled = State;
}

EBodyPartType FWeightedParam::GetReactorBodyPartType()
{
	if (UBodyPart::IsInteraction(Reactor))
	{
		return EBodyPartType::INTERACTION;
	}
	else if (UBodyPart::IsLocomotion(Reactor))
	{
		return EBodyPartType::LOCOMOTION;
	}
	else if (UBodyPart::IsPerception(Reactor))
	{
		return EBodyPartType::PERCEPTION;
	}

	return EBodyPartType::INVALID;
}

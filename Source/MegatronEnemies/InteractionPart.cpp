// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionPart.h"

void UInteractionPart::ExecuteAction_Implementation()
{
	bIsExecutingAction = true;
}

void UInteractionPart::StopAction_Implementation()
{
	bIsExecutingAction = false;
}

bool UInteractionPart::IsExecutingAction() const
{
	return bIsExecutingAction;
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "MegatronEnemiesGameMode.h"
#include "MegatronEnemiesCharacter.h"
#include "UObject/ConstructorHelpers.h"

AMegatronEnemiesGameMode::AMegatronEnemiesGameMode() : Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(
		TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}

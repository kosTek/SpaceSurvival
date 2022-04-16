// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceSurvivalGameMode.h"
#include "SpaceSurvivalCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASpaceSurvivalGameMode::ASpaceSurvivalGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

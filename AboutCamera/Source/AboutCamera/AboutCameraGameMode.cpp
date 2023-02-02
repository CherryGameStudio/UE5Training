// Copyright Epic Games, Inc. All Rights Reserved.

#include "AboutCameraGameMode.h"
#include "AboutCameraCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAboutCameraGameMode::AAboutCameraGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "AboutBoneAnimationGameMode.h"
#include "AboutBoneAnimationCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAboutBoneAnimationGameMode::AAboutBoneAnimationGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

// Copyright Epic Games, Inc. All Rights Reserved.

#include "EnhanceInputTrainingGameMode.h"
#include "EnhanceInputTrainingCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEnhanceInputTrainingGameMode::AEnhanceInputTrainingGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

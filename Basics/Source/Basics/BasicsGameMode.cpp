// Copyright Epic Games, Inc. All Rights Reserved.

#include "BasicsGameMode.h"
#include "BasicsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABasicsGameMode::ABasicsGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

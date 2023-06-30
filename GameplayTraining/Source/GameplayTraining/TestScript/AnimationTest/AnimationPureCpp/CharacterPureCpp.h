// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTraining/TestScript/AnimationTest/Base/MyCharacterBase.h"
#include "CharacterPureCpp.generated.h"

class UAnimSequenceBase;

UCLASS()
class GAMEPLAYTRAINING_API ACharacterPureCpp : public AMyCharacterBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	UAnimSequenceBase* AnimA;

	UPROPERTY(EditAnywhere)
	UAnimSequenceBase* AnimB;
};

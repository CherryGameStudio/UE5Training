// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UObject/UObjectGlobals.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class UNREALENGINETRAINING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

protected:
	void BeginPlay() override;
};

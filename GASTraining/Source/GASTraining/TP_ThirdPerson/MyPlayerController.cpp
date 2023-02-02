// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "TP_ThirdPersonCharacter.h"


void AMyPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	UE_LOG(LogTemp, Warning, TEXT("AMyPlayerController OnPossess"));
	
	ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(InPawn);
	if (MyCharacter)
	{
		MyCharacter->InitializeAbilitySystem();
	}
}

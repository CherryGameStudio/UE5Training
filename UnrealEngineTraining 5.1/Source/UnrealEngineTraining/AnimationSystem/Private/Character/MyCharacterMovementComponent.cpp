// Fill out your copyright notice in the Description page of Project Settings.

#include "UnrealEngineTraining/AnimationSystem/Public/Character/MyCharacterMovementComponent.h"

UMyCharacterMovementComponent::UMyCharacterMovementComponent(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
}

FRotator UMyCharacterMovementComponent::ComputeOrientToMovementRotation(const FRotator& CurrentRotation,
	float DeltaTime, FRotator& DeltaRotation) const
{
	if (IsSwimming())
	{
		return Super::ComputeOrientToMovementRotation(CurrentRotation, DeltaTime, DeltaRotation);
	}
	
	return GetPawnOwner()->Controller->GetControlRotation();
}



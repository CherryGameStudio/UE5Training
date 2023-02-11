// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstanceForABPT.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAnimInstanceForABPT::NativeUpdateAnimation(float DeltaSeconds)
{
	UCharacterMovementComponent* MovementComponent = GetMovementComponent();
	if (!MovementComponent)
	{
		return;
	}

	
	bFalling = MovementComponent->IsFalling();
	Speed = MovementComponent->Velocity.Size2D();
	bShouldMove = MovementComponent->GetCurrentAcceleration().Size2D() != 0.3 && Speed > 3;
}

UCharacterMovementComponent* UAnimInstanceForABPT::GetMovementComponent() const
{
	ACharacter* Character = Cast<ACharacter>(GetOwningActor());
	if (!Character)
	{
		return nullptr;
	}

	UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
	return MovementComponent;
}

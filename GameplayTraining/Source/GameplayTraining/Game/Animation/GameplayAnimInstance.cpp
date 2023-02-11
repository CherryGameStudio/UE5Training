// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAnimInstance.h"

#include "GameplayTraining/Game/Character/GameCharacterMovementComponent.h"
#include "GameplayTraining/Game/Character/GameplayCharacter.h"

void UGameplayAnimInstance::NativeInitializeAnimation()
{
	USkeletalMeshComponent* SkeletalMeshComponent = GetSkelMeshComponent();
	check(SkeletalMeshComponent);
}

void UGameplayAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	UGameCharacterMovementComponent* CharacterMovementComponent = GetMovementComponent();
	if (!CharacterMovementComponent)
	{
		return;
	}

	
	Speed = CharacterMovementComponent->Velocity.Size2D();
	bShouldMove = CharacterMovementComponent->GetCurrentAcceleration().Size2D() > 0 && Speed > 3;
}

UGameCharacterMovementComponent* UGameplayAnimInstance::GetMovementComponent() const
{
	AGameplayCharacter* GameplayCharacter = Cast<AGameplayCharacter>(GetOwningActor());
	if (GameplayCharacter)
	{
		return Cast<UGameCharacterMovementComponent>(GameplayCharacter->GetCharacterMovement());
	}

	return nullptr;
}

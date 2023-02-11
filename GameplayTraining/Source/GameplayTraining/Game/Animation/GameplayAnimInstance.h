// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayAnimInstance.generated.h"

class UGameCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class GAMEPLAYTRAINING_API UGameplayAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	UGameCharacterMovementComponent* GetMovementComponent() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove;

	UPROPERTY(BlueprintReadOnly)
	float Speed;
};

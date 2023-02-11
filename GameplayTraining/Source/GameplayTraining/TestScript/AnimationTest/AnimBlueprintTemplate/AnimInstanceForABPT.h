// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceForABPT.generated.h"

class UCharacterMovementComponent;

/**
 * 
 */
UCLASS()
class GAMEPLAYTRAINING_API UAnimInstanceForABPT : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	UCharacterMovementComponent* GetMovementComponent() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	bool bShouldMove;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	bool bFalling;
};

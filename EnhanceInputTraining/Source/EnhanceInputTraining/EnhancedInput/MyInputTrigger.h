// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "MyInputTrigger.generated.h"

/**
 * 
 */
UCLASS(NotBlueprintable, meta = (DisplayName = "Cherry_Breath"))
class UMyInputTrigger : public UInputTriggerTimedBase
{
	GENERATED_BODY()

protected:
	virtual ETriggerState UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput, FInputActionValue ModifiedValue, float DeltaTime) override;

	bool bTriggered = false;

	float InRangeDuration = 0.0f;
	
	int BreathCount = 0;
	
public:
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings")
	bool BeginWithTrigger;
	
	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))
	float TriggerTime;

	UPROPERTY(EditAnywhere, Config, BlueprintReadWrite, Category = "Trigger Settings", meta = (ClampMin = "0"))
	float UnTriggerTime;
};

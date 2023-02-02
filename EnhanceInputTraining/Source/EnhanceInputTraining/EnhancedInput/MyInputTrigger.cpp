// Fill out your copyright notice in the Description page of Project Settings.


#include "MyInputTrigger.h"

#include "EnhancedPlayerInput.h"

ETriggerState UMyInputTrigger::UpdateState_Implementation(const UEnhancedPlayerInput* PlayerInput,
                                                          FInputActionValue ModifiedValue, float DeltaTime)
{
	// Transition to Ongoing on actuation. Update the held duration.
	if (IsActuated(ModifiedValue))
	{

		if(ensureMsgf(PlayerInput && PlayerInput->GetOuterAPlayerController(), TEXT("No Player Input was given to Calculate with! Returning 1.0")))
		{
			const float TimeDilation = PlayerInput->GetOuterAPlayerController()->GetActorTimeDilation();
	
			// Calculates the new held duration, applying time dilation if desired
			HeldDuration = HeldDuration + (!bAffectedByTimeDilation ? DeltaTime : DeltaTime * TimeDilation);
			InRangeDuration = InRangeDuration + (!bAffectedByTimeDilation ? DeltaTime : DeltaTime * TimeDilation);
		}
		else
		{
			HeldDuration = 1.0f;
			InRangeDuration = 1.0f;
		}
	}
	else
	{
		// Reset duration
		HeldDuration = 0.0f;
		InRangeDuration = 0.0f;
		BreathCount = 0;
	}
	
	float TotalBreathTime = TriggerTime + UnTriggerTime;
	while (InRangeDuration > TotalBreathTime)
	{
		InRangeDuration = InRangeDuration - TotalBreathTime;
		BreathCount++;
	}

	if (IsActuated(ModifiedValue))
	{
		if (BeginWithTrigger)
		{
			if (InRangeDuration < TriggerTime)
			{
				bTriggered = true;
			}
			else
			{
				bTriggered = false;
			}
		}
		else
		{
			if (InRangeDuration < UnTriggerTime)
			{
				bTriggered = false;
			}
			else
			{
				bTriggered = true;
			}
		}

		UE_LOG(LogTemp, Log, TEXT("BREATH COUNT:%d"), BreathCount);
		if (bTriggered)
		{
			return  ETriggerState::Triggered;
		}
		else
		{
			return ETriggerState::Ongoing;
		}
	}
	
	return ETriggerState::None;
}

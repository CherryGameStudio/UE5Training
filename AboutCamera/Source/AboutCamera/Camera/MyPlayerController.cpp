// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"

float AMyPlayerController::GetCameraAspectRadio() const
{
	ACharacter* LocalCharacter = GetCharacter();
	if (!LocalCharacter)
	{
		return 0;
	}

	UCameraComponent* CameraComp = Cast<UCameraComponent>(LocalCharacter->GetComponentByClass(UCameraComponent::StaticClass()));
	if (CameraComp && CameraComp->bConstrainAspectRatio)
	{
		return CameraComp->AspectRatio;
	}
	else if (CameraComp && !CameraComp->bConstrainAspectRatio)
	{
		int32 XSize = 0;
		int32 YSize = 0;
		GetViewportSize(XSize, YSize);
		return  static_cast<float>(XSize) / static_cast<float>(YSize);
	}
	else
	{
		return PlayerCameraManager.Get()->DefaultAspectRatio;
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCameraModeStack.h"

#include "GameplayCameraMode.h"

void UGameplayCameraModeStack::PushCameraMode(TSubclassOf<UGameplayCameraMode> CameraMode)
{
	
}

void UGameplayCameraModeStack::EvaluateStack(float DeltaTime, FGameplayCameraModeView& OutCameraMode)
{
	UpdateStack(DeltaTime);
	BlendStack(DeltaTime, OutCameraMode);
}

void UGameplayCameraModeStack::UpdateStack(float DeltaTime)
{
	for (UGameplayCameraMode* CameraMode : CameraModeStack)
	{
		CameraMode->Update(DeltaTime);
	}
}

void UGameplayCameraModeStack::BlendStack(float DeltaTime, FGameplayCameraModeView& OutCameraMode)
{
	for (UGameplayCameraMode* CameraMode : CameraModeStack)
	{
		CameraMode->Blend(OutCameraMode);
	}
}

UGameplayCameraMode* UGameplayCameraModeStack::GetCameraModeInstance(TSubclassOf<UGameplayCameraMode> CameraModeClass)
{
	for (UGameplayCameraMode* CameraMode : CameraModeInstances)
	{
		if (CameraMode && CameraMode->GetClass() == CameraModeClass)
		{
			return CameraMode;
		}
	}

	UGameplayCameraMode* NewCameraMode = NewObject<UGameplayCameraMode>(this, CameraModeClass, NAME_None, RF_NoFlags);
	CameraModeInstances.Add(NewCameraMode);

	return NewCameraMode;
}

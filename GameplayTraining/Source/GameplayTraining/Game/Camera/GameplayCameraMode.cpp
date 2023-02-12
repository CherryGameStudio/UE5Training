// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCameraMode.h"

UGameplayCameraMode::UGameplayCameraMode()
	: CameraModeView()
	, BlendAlpha(0)
	, BlendWeight(0)
{
}

void UGameplayCameraMode::Update(float DeltaTime)
{
	BlendAlpha = FMath::Clamp(BlendAlpha + DeltaTime, 0, 1) ;
}

void UGameplayCameraMode::Blend(FGameplayCameraModeView& CameraMode)
{
}

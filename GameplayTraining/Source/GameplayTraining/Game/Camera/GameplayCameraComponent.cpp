// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayCameraComponent.h"

#include "GameplayCameraMode.h"
#include "GameplayCameraModeStack.h"

void UGameplayCameraComponent::OnRegister()
{
	Super::OnRegister();

	CameraModeStack = NewObject<UGameplayCameraModeStack>(this);
}

void UGameplayCameraComponent::GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView)
{
	//Super::GetCameraView(DeltaTime, DesiredView);

	
}

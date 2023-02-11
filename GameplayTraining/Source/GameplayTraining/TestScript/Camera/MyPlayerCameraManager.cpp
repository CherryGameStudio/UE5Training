// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCameraManager.h"

float AMyPlayerCameraManager::GetCurrentAspectRadio() const
{
	FMinimalViewInfo CurrentPOV = GetCameraCachePOV();

	return CurrentPOV.AspectRatio;
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "GameplayCameraModeStack.generated.h"

class UGameplayCameraMode;
struct FGameplayCameraModeView;

UCLASS()
class UGameplayCameraModeStack : public UObject
{
	GENERATED_BODY()
	
public:
	void PushCameraMode(TSubclassOf<UGameplayCameraMode> CameraMode);
	
	void EvaluateStack(float DeltaTime, FGameplayCameraModeView& OutCameraMode);

protected:
	void UpdateStack(float DeltaTime);

	void BlendStack(float DeltaTime, FGameplayCameraModeView& OutCameraMode);

private:
	UGameplayCameraMode* GetCameraModeInstance(TSubclassOf<UGameplayCameraMode> CameraModeClass);

protected:
	UPROPERTY()
	TArray<UGameplayCameraMode*> CameraModeInstances;

	UPROPERTY()
	TArray<UGameplayCameraMode*> CameraModeStack;
};

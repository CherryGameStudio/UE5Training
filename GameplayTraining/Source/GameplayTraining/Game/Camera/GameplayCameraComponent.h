// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameplayCameraComponent.generated.h"

class UGameplayCameraModeStack;

UCLASS()
class GAMEPLAYTRAINING_API UGameplayCameraComponent : public UCameraComponent
{
	GENERATED_BODY()

public:
	virtual void OnRegister() override;

	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& DesiredView) override;

protected:
	UPROPERTY()
	TObjectPtr<UGameplayCameraModeStack> CameraModeStack;
};

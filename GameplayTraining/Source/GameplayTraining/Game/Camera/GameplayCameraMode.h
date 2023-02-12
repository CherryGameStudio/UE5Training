// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Object.h"
#include "GameplayCameraMode.generated.h"

UENUM(BlueprintType)
enum class EGameplayCameraModeBlendFunction : uint8
{
	// Does a simple linear interpolation.
	Linear,

	// Immediately accelerates, but smoothly decelerates into the target.  Ease amount controlled by the exponent.
	EaseIn,

	// Smoothly accelerates, but does not decelerate into the target.  Ease amount controlled by the exponent.
	EaseOut,

	// Smoothly accelerates and decelerates.  Ease amount controlled by the exponent.
	EaseInOut,

	COUNT	UMETA(Hidden)
};

struct FGameplayCameraModeView
{
	FGameplayCameraModeView()
	: FieldOfView(90)
	, Location(ForceInit)
	, Rotation(ForceInit)
	, ControlRotation(ForceInit)
	{
		
	}

	void Blend(const FGameplayCameraModeView& Other, float OtherWeight)
	{
		FieldOfView = FMath::Lerp(FieldOfView, Other.FieldOfView, OtherWeight);

		const FRotator DeltaRotation = (Other.Rotation - Rotation).GetNormalized();
		Rotation = Rotation + (OtherWeight * DeltaRotation);

		const FRotator DeltaControlRotation = (Other.ControlRotation - ControlRotation).GetNormalized();
		ControlRotation = ControlRotation + (OtherWeight * DeltaControlRotation);
		
		Location = FMath::Lerp(Location, Other.Location, OtherWeight);
		
	}
	
	float FieldOfView;
	FVector Location;
	FRotator Rotation;
	FRotator ControlRotation;
};

// 相机模式
UCLASS()
class GAMEPLAYTRAINING_API UGameplayCameraMode : public UObject
{
	GENERATED_BODY()

public:
	UGameplayCameraMode();
	
	virtual void Update(float DeltaTime);
	
	virtual void Blend(FGameplayCameraModeView& CameraMode);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	FGameplayTag CameraTypeTag;

	// The horizontal field of view (in degrees).
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "5.0", UIMax = "170", ClampMin = "5.0", ClampMax = "170.0"))
	float FieldOfView;

	// Minimum view pitch (in degrees).
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.9", ClampMax = "89.9"))
	float ViewPitchMin;

	// Maximum view pitch (in degrees).
	UPROPERTY(EditDefaultsOnly, Category = "View", Meta = (UIMin = "-89.9", UIMax = "89.9", ClampMin = "-89.9", ClampMax = "89.9"))
	float ViewPitchMax;

	// How long it takes to blend in this mode.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendTime;

	// Function used for blending.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	EGameplayCameraModeBlendFunction BlendFunction;

	// Exponent used by blend functions to control the shape of the curve.
	UPROPERTY(EditDefaultsOnly, Category = "Blending")
	float BlendExponent;

protected:
	FGameplayCameraModeView CameraModeView;

	float BlendAlpha;

	float BlendWeight;
};

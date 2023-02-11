// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

class USkeletalMeshHelperComponent;
enum class EAnimDisplayType : uint8;

/**
 * 
 */
UCLASS(transient, Blueprintable, hideCategories=AnimInstance, BlueprintType, Within=SkeletalMeshComponent)
class GAMEPLAYTRAINING_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	UFUNCTION(BlueprintCallable)
	USkeletalMeshHelperComponent* GetHelperComponent() const;

public:

	// Agt Tool Start
#if WITH_EDITOR
	void DebugLogActiveSequencerPlayer();
#endif

#if WITH_EDITORONLY_DATA
	void GoToBPNode(int32 NodeIndex);
#endif
	// Agt Tool End


protected:
	UPROPERTY(Transient, BlueprintReadOnly)
	EAnimDisplayType AnimDisplay;
	
	// Simple Pose
	UPROPERTY(Transient, BlueprintReadOnly)
	UAnimSequence* SimplePoseAsset;

	UPROPERTY(Transient, BlueprintReadOnly)
	float SimplePoseTime;

	// BlendPose
	UPROPERTY(Transient, BlueprintReadOnly)
	UAnimSequence* BlendPoseAssetA;

	UPROPERTY(Transient, BlueprintReadOnly)
	UAnimSequence* BlendPoseAssetB;

	UPROPERTY(Transient, BlueprintReadOnly)
	float BlendPoseTime;

	UPROPERTY(Transient, BlueprintReadOnly)
	float BlendPoseWidget;

	// Simple Sequence
	UPROPERTY(Transient, BlueprintReadOnly)
	UAnimSequence* SimpleSequenceAsset;

	UPROPERTY(Transient, BlueprintReadOnly)
	float SimpleSequencePlayRate;

	// Blend Sequence
	UPROPERTY(Transient, BlueprintReadOnly)
	UAnimSequence* BlendSequenceAssetA;

	UPROPERTY(Transient, BlueprintReadOnly)
	UAnimSequence* BlendSequenceAssetB;

	UPROPERTY(Transient, BlueprintReadOnly)
	float BlendSequenceWidget;

	UPROPERTY(Transient, BlueprintReadOnly)
	float BlendSequencePlayRate;

	// Ik
	UPROPERTY(Transient, BlueprintReadOnly)
	float FootHeight;
	
	UPROPERTY(Transient, BlueprintReadOnly)
	FVector CurFootLocOffset;

	UPROPERTY(Transient, BlueprintReadOnly)
	FRotator CurFootRotOffset;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkeletalMeshHelperComponent.generated.h"

class UAnimSequence;
class UMyAnimInstance;

UENUM(BlueprintType)
enum class EAnimDisplayType : uint8
{
	SimplePose,
	BlendPose,
	SimpleSequence,
	BlendSequence,
	
	//CustomPose,
};

UCLASS( ClassGroup=(Custom), Blueprintable, meta=(BlueprintSpawnableComponent) )
class ABOUTBONEANIMATION_API USkeletalMeshHelperComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkeletalMeshHelperComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Agt Tool Start
#if WITH_EDITOR
	
	UFUNCTION(CallInEditor, Category = "AGT Tool")
	void DebugLogActiveSequencerPlayer() const;
	
	UFUNCTION(CallInEditor, Category = "AGT Tool")
	void GoToBPNode() const;
#endif

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "AGT Tool")
	int32 NodeIndex;
#endif
	// Agt Tool End



private:
	UMyAnimInstance* GetMyAnimInstance() const;

public:
	UPROPERTY(EditAnywhere)
	EAnimDisplayType AnimDisplay;

	// Simple Pose
	UPROPERTY(EditAnywhere)
	UAnimSequence* SimplePoseAsset;

	UPROPERTY(EditAnywhere)
	float SimplePoseTime;

	// Blend Pose
	UPROPERTY(EditAnywhere)
	UAnimSequence* BlendPoseAssetA;

	UPROPERTY(EditAnywhere)
	UAnimSequence* BlendPoseAssetB;

	UPROPERTY(EditAnywhere)
	float BlendPoseTime;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 1))
	float BlendPoseWidget;

	// Simple Sequence
	UPROPERTY(EditAnywhere)
	UAnimSequence* SimpleSequenceAsset;

	UPROPERTY(EditAnywhere, meta = (ClampMin = -1, ClampMax = 1))
	float SimpleSequencePlayRate;

	// Blend Sequence
	UPROPERTY(EditAnywhere)
	UAnimSequence* BlendSequenceAssetA;

	UPROPERTY(EditAnywhere)
	UAnimSequence* BlendSequenceAssetB;

	UPROPERTY(EditAnywhere, meta = (ClampMin = 0, ClampMax = 1))
	float BlendSequenceWidget;

	UPROPERTY(EditAnywhere, meta = (ClampMin = -1, ClampMax = 1))
	float BlendSequencePlayRate;

	// IK
	UPROPERTY(EditAnywhere)
	float FootHeight = 15;
};

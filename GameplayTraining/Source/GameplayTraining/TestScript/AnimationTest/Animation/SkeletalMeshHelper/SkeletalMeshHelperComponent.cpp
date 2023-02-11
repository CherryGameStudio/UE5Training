// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalMeshHelperComponent.h"

#include "GameplayTraining/TestScript/AnimationTest/Animation/MyAnimInstance.h"


// Sets default values for this component's properties
USkeletalMeshHelperComponent::USkeletalMeshHelperComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USkeletalMeshHelperComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USkeletalMeshHelperComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	SimplePoseTime = FMath::Clamp(SimplePoseTime, 0, SimplePoseAsset->GetPlayLength());

	BlendPoseTime = FMath::Clamp(BlendPoseTime, 0 , FMath::Max(BlendPoseAssetA->GetPlayLength(), BlendPoseAssetB->GetPlayLength()));
}

#if WITH_EDITOR

void USkeletalMeshHelperComponent::DebugLogActiveSequencerPlayer() const
{
	UMyAnimInstance* MyAnimInstance = GetMyAnimInstance();
	if (MyAnimInstance)
	{
		MyAnimInstance->DebugLogActiveSequencerPlayer();
	}
}

void USkeletalMeshHelperComponent::GoToBPNode() const
{
	UMyAnimInstance* MyAnimInstance = GetMyAnimInstance();
	if (MyAnimInstance)
	{
		MyAnimInstance->GoToBPNode(NodeIndex);
	}
}

#endif

UMyAnimInstance* USkeletalMeshHelperComponent::GetMyAnimInstance() const
{
	AActor* OwnerActor = GetOwner();
	if (!OwnerActor)
	{
		return nullptr;
	}

	USkeletalMeshComponent* SkeletalMeshComponent = Cast<USkeletalMeshComponent>(OwnerActor->FindComponentByClass(USkeletalMeshComponent::StaticClass()));
	if (!SkeletalMeshComponent)
	{
		return nullptr;
	}

	return Cast<UMyAnimInstance>(SkeletalMeshComponent->AnimScriptInstance.Get());
}



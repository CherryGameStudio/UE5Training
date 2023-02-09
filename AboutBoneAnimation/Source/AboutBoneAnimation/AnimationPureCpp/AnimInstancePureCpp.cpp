// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstancePureCpp.h"

#include "AnimInstanceProxyPureCpp.h"
#include "SkeletalMeshComponentPureCpp.h"

void UAnimInstancePureCpp::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UAnimInstancePureCpp::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
}

FAnimInstanceProxy* UAnimInstancePureCpp::CreateAnimInstanceProxy()
{
	return new FAnimInstanceProxyPureCpp(this);
}

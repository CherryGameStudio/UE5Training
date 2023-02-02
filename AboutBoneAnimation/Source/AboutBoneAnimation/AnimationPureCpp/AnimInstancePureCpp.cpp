// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstancePureCpp.h"

#include "AnimInstanceProxyPureCpp.h"
#include "SkeletalMeshComponentPureCpp.h"

void UAnimInstancePureCpp::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	USkeletalMeshComponentPureCpp* Mesh = Cast<USkeletalMeshComponentPureCpp>(GetSkelMeshComponent());
	if (!Mesh)
	{
		return;
	}

	FAnimInstanceProxyPureCpp& Proxy = GetProxyOnGameThread<FAnimInstanceProxyPureCpp>();
	Proxy.Sequence = Mesh->Temp;
}

void UAnimInstancePureCpp::NativeUpdateAnimation(float DeltaSeconds)
{

	
	Super::NativeUpdateAnimation(DeltaSeconds);
}

FAnimInstanceProxy* UAnimInstancePureCpp::CreateAnimInstanceProxy()
{
	return new FAnimInstanceProxyPureCpp(this);
}

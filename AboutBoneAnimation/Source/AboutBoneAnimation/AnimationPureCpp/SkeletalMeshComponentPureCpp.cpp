// Fill out your copyright notice in the Description page of Project Settings.


#include "SkeletalMeshComponentPureCpp.h"

#include "AnimCustomInstanceHelper.h"
#include "AnimInstanceProxyPureCpp.h"
#include "AnimInstancePureCpp.h"
#include "Animation/AnimInstance.h"

void USkeletalMeshComponentPureCpp::BeginPlay()
{
	bool bWasCreated = false;
	FAnimCustomInstanceHelper::BindToSkeletalMeshComponent<UAnimInstancePureCpp>(this, bWasCreated);
	
	Super::BeginPlay();
}

void USkeletalMeshComponentPureCpp::TickComponent(float DeltaTime, ELevelTick TickType,
                                                  FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceComponent.h"

#include "Kismet/KismetSystemLibrary.h"

UTraceComponent::UTraceComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTraceComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	if (Owner)
	{
		TraceStartLoc = GetOwner()->GetActorLocation();
		TraceStartRot = GetOwner()->GetActorRotation();
	}
}

void UTraceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Common Params
	AActor* TraceContext = GetOwner();
	FVector Start = TraceStartLoc + TraceStartRelLoc;
	FVector End = Start + (TraceStartRot + TraceStartRelRot).Vector() * TraceLength;
	FHitResult HitResult;
	TArray<FHitResult> TraceHitResults;
	// TArray<FHitResult> HitResults;
	
	switch (TraceType)
	{
	case ETraceComponentType::Channel:
		TraceForChannel(TraceContext, Start, End, HitResult, TraceHitResults);
		break;
	case ETraceComponentType::ObjectType:
		TraceForObjectTypes(TraceContext, Start, End, HitResult, TraceHitResults);
		break;
	case ETraceComponentType::Profile:
		TraceForProfile(TraceContext, Start, End, HitResult, TraceHitResults);
		break;
	default: ;
	}

	if (HitResult.HasValidHitObjectHandle())
	{
		TraceHitResults.Add(HitResult);
	}

	TraceHitResultsVisiable.Reset();
	for (FHitResult EachHitResult : TraceHitResults)
	{
		FHitResultVisiable HitResultVisiable;
		HitResultVisiable = EachHitResult;
		TraceHitResultsVisiable.Add(HitResultVisiable);
	}
}

void UTraceComponent::TraceForChannel(UObject* TraceContext, FVector Start, FVector End, FHitResult& HitResult, TArray<FHitResult>& OutHitResults)
{
	switch (TraceShape)
	{
	case ETraceComponentShape::Line:
		if (bMutiTrace)
			UKismetSystemLibrary::LineTraceMulti(TraceContext, Start, End, TraceChannel, bTraceComplex,
			                                     ActorsToIgnore, DrawDebugType, OutHitResults, bIngoreSelf, TraceColor,
			                                     TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::LineTraceSingle(TraceContext, Start, End, TraceChannel, bTraceComplex,
			                                      ActorsToIgnore, DrawDebugType, HitResult, bIngoreSelf, TraceColor,
			                                      TraceHitColor, DrawTime);
		break;

	case ETraceComponentShape::Sphere:
		if (bMutiTrace)
			UKismetSystemLibrary::SphereTraceMulti(TraceContext, Start, End, SphereRadius, TraceChannel, bTraceComplex,
			                                       ActorsToIgnore, DrawDebugType, OutHitResults, bIngoreSelf,
			                                       TraceColor, TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::SphereTraceSingle(TraceContext, Start, End, SphereRadius, TraceChannel, bTraceComplex,
			                                        ActorsToIgnore, DrawDebugType, HitResult, bIngoreSelf,
			                                        TraceColor, TraceHitColor, DrawTime);
		break;

	case ETraceComponentShape::Capsule:
		if (bMutiTrace)
			UKismetSystemLibrary::CapsuleTraceMulti(TraceContext, Start, End, CapsuleRadius, CapsuleHalfHeight,
			                                        TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType,
			                                        OutHitResults, bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::CapsuleTraceSingle(TraceContext, Start, End, CapsuleRadius, CapsuleHalfHeight,
			                                         TraceChannel, bTraceComplex, ActorsToIgnore, DrawDebugType,
			                                         HitResult, bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		break;

	case ETraceComponentShape::Box:
		if (bMutiTrace)
			UKismetSystemLibrary::BoxTraceMulti(TraceContext, Start, End, BoxExtend, BoxOrientation, TraceChannel,
			                                    bTraceComplex, ActorsToIgnore, DrawDebugType, OutHitResults,
			                                    bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::BoxTraceSingle(TraceContext, Start, End, BoxExtend, BoxOrientation, TraceChannel,
			                                     bTraceComplex, ActorsToIgnore, DrawDebugType, HitResult,
			                                     bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		break;

	default: ;
	}
}

void UTraceComponent::TraceForObjectTypes(UObject* TraceContext, FVector Start, FVector End, FHitResult& HitResult, TArray<FHitResult>& OutHitResults)
{
	switch (TraceShape)
	{
	case ETraceComponentShape::Line:
		if (bMutiTrace)
			UKismetSystemLibrary::LineTraceMultiForObjects(TraceContext, Start, End, TraceObjectTypes, bTraceComplex,
			                                     ActorsToIgnore, DrawDebugType, OutHitResults, bIngoreSelf, TraceColor,
			                                     TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::LineTraceSingleForObjects(TraceContext, Start, End, TraceObjectTypes, bTraceComplex,
			                                      ActorsToIgnore, DrawDebugType, HitResult, bIngoreSelf, TraceColor,
			                                      TraceHitColor, DrawTime);
		break;

	case ETraceComponentShape::Sphere:
		if (bMutiTrace)
			UKismetSystemLibrary::SphereTraceMultiForObjects(TraceContext, Start, End, SphereRadius, TraceObjectTypes, bTraceComplex,
			                                       ActorsToIgnore, DrawDebugType, OutHitResults, bIngoreSelf,
			                                       TraceColor, TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::SphereTraceSingleForObjects(TraceContext, Start, End, SphereRadius, TraceObjectTypes, bTraceComplex,
			                                        ActorsToIgnore, DrawDebugType, HitResult, bIngoreSelf,
			                                        TraceColor, TraceHitColor, DrawTime);
		break;

	case ETraceComponentShape::Capsule:
		if (bMutiTrace)
			UKismetSystemLibrary::CapsuleTraceMultiForObjects(TraceContext, Start, End, CapsuleRadius, CapsuleHalfHeight,
			                                        TraceObjectTypes, bTraceComplex, ActorsToIgnore, DrawDebugType,
			                                        OutHitResults, bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::CapsuleTraceSingleForObjects(TraceContext, Start, End, CapsuleRadius, CapsuleHalfHeight,
			                                         TraceObjectTypes, bTraceComplex, ActorsToIgnore, DrawDebugType,
			                                         HitResult, bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		break;

	case ETraceComponentShape::Box:
		if (bMutiTrace)
			UKismetSystemLibrary::BoxTraceMultiForObjects(TraceContext, Start, End, BoxExtend, BoxOrientation, TraceObjectTypes,
			                                    bTraceComplex, ActorsToIgnore, DrawDebugType, OutHitResults,
			                                    bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::BoxTraceSingleForObjects(TraceContext, Start, End, BoxExtend, BoxOrientation, TraceObjectTypes,
			                                     bTraceComplex, ActorsToIgnore, DrawDebugType, HitResult,
			                                     bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		break;

	default: ;
	}
}

void UTraceComponent::TraceForProfile(UObject* TraceContext, FVector Start, FVector End, FHitResult& HitResult, TArray<FHitResult>& OutHitResults)
{
	switch (TraceShape)
	{
	case ETraceComponentShape::Line:
		if (bMutiTrace)
			UKismetSystemLibrary::LineTraceMultiByProfile(TraceContext, Start, End, ProfileName, bTraceComplex,
			                                     ActorsToIgnore, DrawDebugType, OutHitResults, bIngoreSelf, TraceColor,
			                                     TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::LineTraceSingleByProfile(TraceContext, Start, End, ProfileName, bTraceComplex,
			                                      ActorsToIgnore, DrawDebugType, HitResult, bIngoreSelf, TraceColor,
			                                      TraceHitColor, DrawTime);
		break;

	case ETraceComponentShape::Sphere:
		if (bMutiTrace)
			UKismetSystemLibrary::SphereTraceMultiByProfile(TraceContext, Start, End, SphereRadius, ProfileName, bTraceComplex,
			                                       ActorsToIgnore, DrawDebugType, OutHitResults, bIngoreSelf,
			                                       TraceColor, TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::SphereTraceSingleByProfile(TraceContext, Start, End, SphereRadius, ProfileName, bTraceComplex,
			                                        ActorsToIgnore, DrawDebugType, HitResult, bIngoreSelf,
			                                        TraceColor, TraceHitColor, DrawTime);
		break;

	case ETraceComponentShape::Capsule:
		if (bMutiTrace)
			UKismetSystemLibrary::CapsuleTraceMultiByProfile(TraceContext, Start, End, CapsuleRadius, CapsuleHalfHeight,
			                                        ProfileName, bTraceComplex, ActorsToIgnore, DrawDebugType,
			                                        OutHitResults, bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::CapsuleTraceSingleByProfile(TraceContext, Start, End, CapsuleRadius, CapsuleHalfHeight,
			                                         ProfileName, bTraceComplex, ActorsToIgnore, DrawDebugType,
			                                         HitResult, bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		break;

	case ETraceComponentShape::Box:
		if (bMutiTrace)
			UKismetSystemLibrary::BoxTraceMultiByProfile(TraceContext, Start, End, BoxExtend, BoxOrientation, ProfileName,
			                                    bTraceComplex, ActorsToIgnore, DrawDebugType, OutHitResults,
			                                    bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		else
			UKismetSystemLibrary::BoxTraceSingleByProfile(TraceContext, Start, End, BoxExtend, BoxOrientation, ProfileName,
			                                     bTraceComplex, ActorsToIgnore, DrawDebugType, HitResult,
			                                     bIngoreSelf, TraceColor, TraceHitColor, DrawTime);
		break;

	default: ;
	}
}

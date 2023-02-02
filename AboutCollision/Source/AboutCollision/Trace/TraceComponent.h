// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AboutCollision/CollisionTypes.h"
#include "Components/ActorComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TraceComponent.generated.h"

UENUM(BlueprintType)
enum class ETraceComponentShape : uint8
{
	Line,
	Sphere,
	Capsule,
	Box
};

UENUM(BlueprintType)
enum class ETraceComponentType : uint8
{
	Channel,
	ObjectType,
	Profile,
};

// 用于辅助进行Trace的组件
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ABOUTCOLLISION_API UTraceComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTraceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void TraceForChannel(UObject* TraceContext, FVector Start, FVector End, FHitResult& HitResult, TArray<FHitResult>& OutHitResults);

	void TraceForObjectTypes(UObject* TraceContext, FVector Start, FVector End, FHitResult& HitResult, TArray<FHitResult>& OutHitResults);

	void TraceForProfile(UObject* TraceContext, FVector Start, FVector End, FHitResult& HitResult, TArray<FHitResult>& OutHitResults);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FVector TraceStartLoc;

	FRotator TraceStartRot;

	// UPROPERTY()
	TArray<AActor*> ActorsToIgnore;
	
	// Trace Config
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common")
	FVector TraceStartRelLoc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common")
	FRotator TraceStartRelRot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common")
	float TraceLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common")
	bool bMutiTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common")
	ETraceComponentShape TraceShape;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common")
	ETraceComponentType TraceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common")
	bool bIngoreSelf;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common")
	bool bTraceComplex;

	// ~Type Begin~
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common", meta = (EditCondition = "TraceType == ETraceComponentType::Channel", EditConditionHides))
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common", meta = (EditCondition = "TraceType == ETraceComponentType::ObjectType", EditConditionHides))
	TArray<TEnumAsByte<EObjectTypeQuery> > TraceObjectTypes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Common", meta = (EditCondition = "TraceType == ETraceComponentType::Profile", EditConditionHides))
	FName ProfileName;
	// ~Type End~
	
	// ~Shape Begin~
	// Sphere
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Sphere", meta = (EditCondition = "TraceShape == ETraceComponentShape::Sphere", EditConditionHides))
	float SphereRadius = 10;
	
	// Capsule
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Capsule", meta = (EditCondition = "TraceShape == ETraceComponentShape::Capsule", EditConditionHides))
	float CapsuleRadius = 10;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Capsule", meta = (EditCondition = "TraceShape == ETraceComponentShape::Capsule", EditConditionHides))
	float CapsuleHalfHeight = 20;
	
	// Box
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Box", meta = (EditCondition = "TraceShape == ETraceComponentShape::Box", EditConditionHides))
	FVector BoxExtend = FVector(5, 5, 5);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Box", meta = (EditCondition = "TraceShape == ETraceComponentShape::Box", EditConditionHides))
	FRotator BoxOrientation = FRotator(0, 0, 0);
	// ~Shape End~
	
	// Debug
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Debug")
	TEnumAsByte<EDrawDebugTrace::Type> DrawDebugType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Debug", meta = (EditCondition = "DrawDebugType != EDrawDebugTrace::None", EditConditionHides))
	FLinearColor TraceColor = FLinearColor::Green;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Debug", meta = (EditCondition = "DrawDebugType != EDrawDebugTrace::None", EditConditionHides))
	FLinearColor TraceHitColor = FLinearColor::Red;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trace|Debug", meta = (EditCondition = "DrawDebugType == EDrawDebugTrace::ForDuration", EditConditionHides))
	float DrawTime = 5.0f;

	// HitResult
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Trace|HitResult")
	TArray<FHitResultVisiable> TraceHitResultsVisiable;
};

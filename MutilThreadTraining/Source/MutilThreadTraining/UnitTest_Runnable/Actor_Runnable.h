// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Actor_Runnable.generated.h"

UCLASS()
class MUTILTHREADTRAINING_API AActor_Runnable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActor_Runnable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
	void Unit_Test1();

	UFUNCTION(CallInEditor)
	void Unit_Test2();

	void SetCurrentRunCount(int32 InCurrentRunCount) { CurrentRunCount = InCurrentRunCount; }

	int32 GetCurrentRunCount() const { return CurrentRunCount; }

	int32 GetTotalTargetRunCount() const { return TotalTargetRunCount; }
	
public:
	UPROPERTY(EditAnywhere)
	int32 TotalTargetRunCount;

	int32 CurrentRunCount;

	UPROPERTY(EditAnywhere)
	uint8 ThreadCount;
	
	UPROPERTY(EditAnywhere)
	bool bEnableTickCount;
	
	int32 TickCount;
};

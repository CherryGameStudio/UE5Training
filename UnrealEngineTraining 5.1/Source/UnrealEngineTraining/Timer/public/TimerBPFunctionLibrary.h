// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TimerBPFunctionLibrary.generated.h"

class FTimerManager;
class UTimerObject;

/**
 * 
 */
UCLASS()
class UNREALENGINETRAINING_API UTimerBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	//FTimerManager Native Usage
public:
	UFUNCTION(BlueprintCallable)
	static void SetTimerByUObject(FTimerHandle& inOutHandle, int rate, bool isLoop = false, float firstDelay = 0.0f);
	
	UFUNCTION(BlueprintCallable)
	static void SetTimerByDelegate(FTimerHandle& inOutHandle, int rate, bool isLoop = false, float firstDelay = 0.0f);
	
	UFUNCTION(BlueprintCallable)
	static void SetTimerByLambda(FTimerHandle& inOutHandle, int rate, bool isLoop = false, float firstDelay = 0.0f);

	
	//FMyTimerManager Usage
	UFUNCTION(BlueprintCallable)
	static int32 SetMyTimerByLambda(int rate, bool isLoop = false, float firstDelay = 0.0f);
public:
};

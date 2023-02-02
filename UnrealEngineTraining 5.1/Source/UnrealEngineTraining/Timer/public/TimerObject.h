// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TimerObject.generated.h"

/**
 * 
 */
UCLASS()
class UNREALENGINETRAINING_API UTimerObject : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void PrintFunction();
	
};

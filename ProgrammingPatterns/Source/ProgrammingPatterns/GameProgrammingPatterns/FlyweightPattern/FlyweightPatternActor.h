// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FlyweightPatternActor.generated.h"

UCLASS()
class PROGRAMMINGPATTERNS_API AFlyweightPatternActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFlyweightPatternActor();

public:
	UPROPERTY(EditAnywhere, Category = "Flyweight Sample", meta = (ClampMin = "0", ClampMax = "10000"))
	int32 WebsiteNum;

	UPROPERTY(EditAnywhere, Category = "Flyweight Sample")
	TArray<FString> WebsiteNames;

	UFUNCTION(CallInEditor, Category = "Flyweight Sample")
	void ApplyFlyweightSample();
};

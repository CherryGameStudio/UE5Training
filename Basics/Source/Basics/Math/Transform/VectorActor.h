// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VectorActor.generated.h"

class UStaticMeshComponent;

// Learn About Vector Demo as Actor
UCLASS()
class BASICS_API AVectorActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AVectorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
	void ExplainVector() const;

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere)
	bool bShouldMove;
	
	UPROPERTY(EditAnywhere)
	FVector Vector1;

	UPROPERTY(EditAnywhere)
	FVector Vec2;
};

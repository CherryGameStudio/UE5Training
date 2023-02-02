// Fill out your copyright notice in the Description page of Project Settings.


#include "ObserverPatternActor.h"

// Sets default values
AObserverPatternActor::AObserverPatternActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObserverPatternActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AObserverPatternActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


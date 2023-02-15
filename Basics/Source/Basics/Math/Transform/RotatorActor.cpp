// Fill out your copyright notice in the Description page of Project Settings.


#include "RotatorActor.h"


// Sets default values
ARotatorActor::ARotatorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ARotatorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARotatorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ARotatorActor::ExplainRotator()
{
	FRotator LocalRotator1 = Rotator1;


	Rotator1.RotateVector()
}


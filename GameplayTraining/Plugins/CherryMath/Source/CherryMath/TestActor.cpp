// Fill out your copyright notice in the Description page of Project Settings.


#include "TestActor.h"

#include "Geometry/Ray.h"


// Sets default values
ATestActor::ATestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	// 两线🍌算法	Intersection of Two Lines in 3D Space
	// https://www.youtube.com/watch?v=N-qUfr-rz_Y&list=PL3d-XcUlfFv7Q6WCP1yJyN50CDwjGvrLs

	
	UWorld* World = GetWorld();
	if (World)
	{
		// 将两条线段画线
		DrawDebugLine(World, Origin1 - Direction1 * 500, Origin1 + Direction1 * 500, FColor::Green);
		DrawDebugLine(World, Origin2 - Direction2 * 500, Origin2 + Direction2 * 500, FColor::Green);
	}


	// 1.获取t2
	float t1 = 0;
	float t2 = 0;
	bool bIntersection = false;
	float Value1 = Direction2.Y * Direction1.X - Direction2.X * Direction1.Y;
	if (Value1 == 0)
	{
		FVector OriDelNormal = (Origin2 - Origin1).GetSafeNormal().GetAbs();
		FVector DirNormal1 = Direction1.GetSafeNormal().GetAbs();
		FVector DirNormal2 = Direction2.GetSafeNormal().GetAbs();
		if (DirNormal1 == DirNormal2)
		{
			UE_LOG(LogTemp, Log, TEXT("%s      %s"), *OriDelNormal.ToString(), *DirNormal1.ToString());
			if (Origin1 == Origin2 || OriDelNormal == DirNormal1)
			{
				UE_LOG(LogTemp, Log, TEXT("共线"));
			}
			else
			{
				UE_LOG(LogTemp, Log, TEXT("平行"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("不共面"));
		}
	}
	else
	{
		// 将X式,Y式带入得出t1和t2
		t2 = ((Origin2.X - Origin1.X) * Direction1.Y - (Origin2.Y - Origin1.Y) * Direction1.X) / Value1;
		if (Direction1.X != 0)
		{
			t1 = (t2 * Direction2.X + Origin2.X - Origin1.X) / Direction1.X;
		}
		else if (Direction2.Y != 0)
		{
			t1 = (t2 * Direction2.Y + Origin2.Y - Origin1.Y) / Direction1.Y;
		}
		else
		{
			t1 = (t2 * Direction2.Z + Origin2.Z - Origin1.Z) / Direction1.Z;
		}

		// 将t1和t2带入Z式
		if (Origin1.Z + Direction1.Z * t1 == Origin2.Z + Direction2.Z * t2)
		{
			//相交
			bIntersection = true;
			UE_LOG(LogTemp, Log, TEXT("相交"));
		}
		else
		{
			//不共面
			UE_LOG(LogTemp, Log, TEXT("不共面"));
		}
	}
	if (bIntersection)
	{
		FVector IntersectionPoint = Origin1 + t1 * Direction1;
		if (World)
		{
			DrawDebugSphere(World, IntersectionPoint, 2, 20, FColor::Red);
		}
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyweightPatternActor.h"

#include "FlyweightSample.h"

// Sets default values
AFlyweightPatternActor::AFlyweightPatternActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFlyweightPatternActor::ApplyFlyweightSample()
{
	int32 WebsiteTypeNum = WebsiteNames.Num();
	if (WebsiteTypeNum > 0)
	{
		TArray<FlyweightObject*> Array;
		for (int32 i = 0; i < WebsiteNum; i++)
		{
			int32 UserID = FMath::RandRange(0,999);
			int32 Type = FMath::RandRange(0,WebsiteTypeNum-1);
			FString WebsiteName = WebsiteNames[Type];
			FlyweightObject* NewObject = new FlyweightObject(UserID, WebsiteName);
			Array.Add(NewObject);
		}

		for (FlyweightObject* Object : Array)
		{
			Object->Print();
			delete Object;
		}

		//delete[] &Array[0];
	}
}


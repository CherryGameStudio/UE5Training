// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealEngineTraining/Timer/public/TimerBPFunctionLibrary.h"

#include "UnrealEngineTraining/Timer/public/TimerModule.h"
#include "UnrealEngineTraining/Timer/Public/TimerObject.h"

static FTimerManager& GetTimerManager()
{
	UWorld* world = GWorld;
	UGameInstance* gameInstance = world->GetGameInstance();
	return gameInstance->GetTimerManager();
}

void UTimerBPFunctionLibrary::SetTimerByUObject(
	FTimerHandle& inOutHandle,
	int rate,
	bool isLoop,
	float firstDelay)
{
	FTimerHandle handle;
	UTimerObject* timerObject = NewObject<UTimerObject>();
	//timerObject->AddToRoot();   会GC哦~
	GetTimerManager().SetTimer(inOutHandle, timerObject, &UTimerObject::PrintFunction, rate, isLoop, firstDelay);
}

void UTimerBPFunctionLibrary::SetTimerByDelegate(
	FTimerHandle& inOutHandle,
	int rate,
	bool isLoop,
	float firstDelay)
{
	GetTimerManager().SetTimer(inOutHandle, FTimerDelegate::CreateLambda([]()
	{
		UE_LOG(LogTemp, Warning, TEXT("Delegate Timer!"))
	}), rate, isLoop, firstDelay);
}

void UTimerBPFunctionLibrary::SetTimerByLambda(
	FTimerHandle& inOutHandle,
	int rate, bool
	isLoop,
	float firstDelay)
{
	GetTimerManager().SetTimer(inOutHandle, []()
	{
		UE_LOG(LogTemp, Warning, TEXT("Lambda Timer!"))
	}, rate, isLoop, firstDelay);
}

int32 UTimerBPFunctionLibrary::SetMyTimerByLambda(int rate, bool isLoop, float firstDelay)
{
	FTimerModule& module = FTimerModule::Instance();
	return module.SetTimer([]()
	{
		UE_LOG(LogTemp, Warning, TEXT("FTimerModule Lambda Timer!"))
	},rate,isLoop,firstDelay);
}


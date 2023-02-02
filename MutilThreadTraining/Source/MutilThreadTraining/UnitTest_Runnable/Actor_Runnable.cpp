// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor_Runnable.h"

#include "RunnableThread_UnitTest.h"
#include "Runnable_UnitTest1.h"
#include "Runnable_UnitTest2.h"

// Sets default values
AActor_Runnable::AActor_Runnable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActor_Runnable::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void AActor_Runnable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bEnableTickCount)
	{
		UE_LOG(LogTemp, Warning, TEXT("AActor_Runnable::Tick In GameThread, TickCount : %d."), ++TickCount);
	}
	
}

void AActor_Runnable::Unit_Test1()
{
	TickCount = 0;
	CurrentRunCount = 0;

	// 测试发现，创建的线程数量越多，效率越低，因为时间都消耗在CPU切换时间分片上了。
	for (int ThreadID = 1; ThreadID < ThreadCount + 1; ++ThreadID)
	{
		FString ThreadName = FString::Format(TEXT("线程{0}"), {ThreadID});
		FRunnable_UnitTest1* Runnable = new FRunnable_UnitTest1(ThreadName, this);
		FRunnableThread* RunnableThread = FRunnableThread::Create(Runnable, *ThreadName);
	}
}

void AActor_Runnable::Unit_Test2()
{
	TickCount = 0;
	CurrentRunCount = 0;

	int32 EachProcessCount = TotalTargetRunCount / ThreadCount;
	int32 LastAdditionCount = TotalTargetRunCount % ThreadCount;

	UE_LOG(LogTemp, Warning, TEXT("EachProcessCount:%d, LastAdditionCount:%d"), EachProcessCount, LastAdditionCount);

	// 相比较Unit_Test1，这次是共同完成相同的任务量，且不会有抢占情况，线程越多效率越高。
	for (int ThreadID = 1; ThreadID < ThreadCount + 1; ++ThreadID)
	{
		int32 RunCount = ThreadID == ThreadCount ? EachProcessCount + LastAdditionCount : EachProcessCount;
		
		FString ThreadName = FString::Format(TEXT("线程{0}"), {ThreadID});
		FRunnable_UnitTest2* Runnable = new FRunnable_UnitTest2(ThreadName, this, RunCount);
		FRunnableThread* RunnableThread = FRunnableThread::Create(Runnable, *ThreadName);
	}
}


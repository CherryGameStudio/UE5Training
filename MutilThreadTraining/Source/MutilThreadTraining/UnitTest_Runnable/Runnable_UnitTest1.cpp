#include "Runnable_UnitTest1.h"

#include "Actor_Runnable.h"
//#include "Misc/ScopeLock.h"

FCriticalSection FRunnable_UnitTest1::CriticalSection;

FRunnable_UnitTest1::FRunnable_UnitTest1(FString InThreadName, AActor* InTargetActor)
{
	ThreadName = InThreadName;
	TargetActor = InTargetActor;

	RunCount = 0;
	TotalElapseTime = 0;
}

bool FRunnable_UnitTest1::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("%s (Thread) Init."), *ThreadName);
	TotalElapseTime = TargetActor->GetWorld()->GetTimeSeconds();
	
	return FRunnable::Init();
}

uint32 FRunnable_UnitTest1::Run()
{
	UE_LOG(LogTemp, Warning, TEXT("%s (Thread) Run."), *ThreadName);
	
	AActor_Runnable* RunnableActor = Cast<AActor_Runnable>(TargetActor);
	if (!RunnableActor)
	{
		return 0;
	}

	while (RunnableActor->CurrentRunCount < RunnableActor->TotalTargetRunCount)
	{
		FScopeLock Lock(&CriticalSection);
		
		RunnableActor->CurrentRunCount++;
		RunCount++;
	}
	
	return 0;
}

void FRunnable_UnitTest1::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("%s (Thread) Stop."), *ThreadName);
	
	FRunnable::Stop();
}

void FRunnable_UnitTest1::Exit()
{
	float DeltaTime = TargetActor->GetWorld()->GetTimeSeconds() - TotalElapseTime;
	UE_LOG(LogTemp, Warning, TEXT("%s (Thread) Exit, TotatRunCount:%d, TotatTime:%f."), *ThreadName, RunCount, DeltaTime);
	
	FRunnable::Exit();
}

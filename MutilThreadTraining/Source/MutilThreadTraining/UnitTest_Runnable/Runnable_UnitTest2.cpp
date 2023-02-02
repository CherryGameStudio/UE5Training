#include "Runnable_UnitTest2.h"

#include "Actor_Runnable.h"

FCriticalSection FRunnable_UnitTest2::CriticalSection;

FRunnable_UnitTest2::FRunnable_UnitTest2(FString InThreadName, AActor* InTargetActor, int32 TotalRunCount)
{
	ThreadName = InThreadName;
	TargetActor = InTargetActor;

	RunCount = TotalRunCount;
	TotalElapseTime = 0;
}

bool FRunnable_UnitTest2::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("%s (Thread) Init."), *ThreadName);

	if (IsValid(TargetActor))
	{
		TotalElapseTime = TargetActor->GetWorld()->GetTimeSeconds();
	}
	
	return FRunnable::Init();
}

uint32 FRunnable_UnitTest2::Run()
{
	UE_LOG(LogTemp, Warning, TEXT("%s (Thread) Run."), *ThreadName);

	AActor_Runnable* RunnableActor = Cast<AActor_Runnable>(TargetActor);
	if (!RunnableActor || !IsValid(RunnableActor))
	{
		return 0;
	}
	
	int AdditionCount = 0;
	for (int Index = 0; Index < RunCount; ++Index)
	{
		AdditionCount++;
		FString Str1 = TEXT("1");
		Str1.Append("2");
	}

	{
		FScopeLock Lock(&CriticalSection);

		RunnableActor->CurrentRunCount += AdditionCount;
	}
	
	return 0;
}

void FRunnable_UnitTest2::Stop()
{
	UE_LOG(LogTemp, Warning, TEXT("%s (Thread) Stop."), *ThreadName);
	
	FRunnable::Stop();
}

void FRunnable_UnitTest2::Exit()
{
	if (IsValid(TargetActor))
	{
		float DeltaTime = TargetActor->GetWorld()->GetTimeSeconds() - TotalElapseTime;
		UE_LOG(LogTemp, Warning, TEXT("%s (Thread) Exit, TotatRunCount:%d, TotatTime:%f."), *ThreadName, RunCount, DeltaTime);
	}
	
	FRunnable::Exit();
}

#pragma once

#include "HAL/Runnable.h"

class FRunnable_UnitTest2 : public FRunnable
{
public:
	FRunnable_UnitTest2(FString InThreadName, AActor* InTargetActor, int32 TotalRunCount);
	
public:
	// FRunnable Implementation
	virtual bool Init() override;

	virtual uint32 Run() override;
	
	virtual void Stop() override;
	
	virtual void Exit() override;
	// FRunnable

	private:
	static FCriticalSection CriticalSection;
	
	FString ThreadName;
	
	AActor* TargetActor;
	
	int32 RunCount;

	float TotalElapseTime;
	
};

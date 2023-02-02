#pragma once

class FTaskGraph_UnitTest
{
public:
	FTaskGraph_UnitTest(FString ThreadName)
		: ThreadName(ThreadName)
	{
		
	}
	
	~FTaskGraph_UnitTest()
	{
		
	}
	
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FTaskGraph_UnitTest, STATGROUP_TaskGraphTasks);
	}

	static ENamedThreads::Type GetDesiredThread()
	{
		return ENamedThreads::AnyThread;
	}

	static FORCEINLINE ESubsequentsMode::Type GetSubsequentsMode()
	{
		return ESubsequentsMode::TrackSubsequents;
	}
	
	void DoTask(ENamedThreads::Type CurrentThread, const FGraphEventRef& MyCompletionGraphEvent)
	{
		UE_LOG(LogTemp, Warning, TEXT("GraphTask Named (%s) Begin Work."), *ThreadName);

		for(int Index = 0; Index < 100000000; Index++)
		{
			FString Str = "1";
			Str.Append("2");
		}

		UE_LOG(LogTemp, Warning, TEXT("GraphTask Named (%s) End Work."), *ThreadName);
	}

private:
	FString ThreadName;
};

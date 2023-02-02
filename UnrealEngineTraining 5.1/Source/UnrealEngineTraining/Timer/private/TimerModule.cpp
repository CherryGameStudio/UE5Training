#include "UnrealEngineTraining/Timer/public/TimerModule.h"


FTimerModule::FTimerModule()
{
}

FTimerModule::~FTimerModule()
{
}

FTimerModule& FTimerModule::Instance()
{
	static  FTimerModule timerModule;
	return timerModule;
}

int32 FTimerModule::SetTimer(TFunction<void(void)>&& callback, float rate, bool isLoop, float firstDelay)
{
	FTimerHandle handle;
	GetTimerManagerInternal().SetTimer(handle, MoveTemp(callback) , rate, isLoop, firstDelay);
	int32 serialId = m_Timers.Add(handle);
	
	return serialId;
}

void FTimerModule::ClearTimer(int32 id)
{
	if (IsExistTimer(id))
	{
		return GetTimerManagerInternal().ClearTimer(m_Timers[id]);
	}
}

void FTimerModule::PauseTimer(int32 id)
{
	if (IsExistTimer(id))
	{
		return GetTimerManagerInternal().PauseTimer(m_Timers[id]);
	}
}

void FTimerModule::UnPauseTimer(int32 id)
{
	if (IsExistTimer(id))
	{
		GetTimerManagerInternal().UnPauseTimer(m_Timers[id]);
	}
}

bool FTimerModule::IsExistTimer(int32 id) const
{
	return m_Timers.IsValidIndex(id);
}

bool FTimerModule::IsTimerActive(int32 id) const
{
	if (IsExistTimer(id))
	{
		return GetTimerManagerInternal().IsTimerActive(m_Timers[id]);
	}
	return false;
}

FTimerHandle FTimerModule::GetTimerHandleInternal(int32 id)
{
	if (IsExistTimer(id))
	{
		return m_Timers[id];
	}
	
	static FTimerHandle InValidHandle; 
	return InValidHandle;
}

FTimerManager& FTimerModule::GetTimerManagerInternal() const
{
	UWorld* world = GWorld;
	UGameInstance* gameInstance = world->GetGameInstance();
	return gameInstance->GetTimerManager();
}


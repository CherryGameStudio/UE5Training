#pragma once

class FTimerModule
{
public:
	FTimerModule();
	~FTimerModule();

	static FTimerModule& Instance();

	int32 SetTimer(TFunction<void(void)>&& callback, float rate, bool isLoop, float firstDelay);
	int32 SetTimer(FTimerDelegate inDelegate, float rate, bool isLoop, float firstDelay);
	//int SetTimer(float rate, TFunction<void>&& callback, bool isLoop, float firstDelay);
	void ClearTimer(int32 id);
	void PauseTimer(int32 id);
	void UnPauseTimer(int32 id);
	bool IsExistTimer(int32 id) const;
	bool IsTimerActive(int32 id) const;

private:
	FTimerHandle GetTimerHandleInternal(int32 id);
	FTimerManager& GetTimerManagerInternal() const;

private:
	TSparseArray<FTimerHandle> m_Timers;
};

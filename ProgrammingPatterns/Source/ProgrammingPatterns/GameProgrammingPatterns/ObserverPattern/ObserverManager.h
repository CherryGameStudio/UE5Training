#pragma once

class ObserverEvent
{
public:
	ObserverEvent(int32 InEventID)
		: EventID(InEventID)
	{}

private:
	int32 EventID;
};

/**
 * 观察者管理器
 */
class ObserverManager
{
public:
	using FuncType = TFunction<void(ObserverEvent*)>;
	
	static ObserverManager& Get()
	{
		static ObserverManager* Manager = nullptr;
		if (!Manager)
		{
			Manager = new ObserverManager();
		}

		return *Manager;
	}
	
	void Register(int32 EventID, FuncType Function);

	void UnRegister();

	void Fire(ObserverEvent* Event);

private:
	struct ListenerData
	{
		ListenerData(FuncType InFunction)
			:Function(InFunction)
		{}
		
		FuncType Function;
	};
	
	struct ListenerDataList
	{
		TArray<ListenerDataList> ListenerList;
	};

	TMap<int32, ListenerDataList> ObserverMap;
};

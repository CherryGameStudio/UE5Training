#include "ObserverManager.h"

void ObserverManager::Register(int32 EventID, FuncType Function)
{
	ListenerData Data = ListenerData(Function);
}

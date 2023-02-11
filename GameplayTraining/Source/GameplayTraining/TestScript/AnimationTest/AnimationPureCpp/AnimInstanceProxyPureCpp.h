#pragma once
#include "Animation/AnimInstanceProxy.h"

//struct FAnimNode_Base;
struct FAnimNode_SequencePlayer;

class FAnimInstanceProxyPureCpp : public FAnimInstanceProxy
{
public:
	FAnimInstanceProxyPureCpp(UAnimInstance* Instance)
		: FAnimInstanceProxy(Instance)
	{
	}
	
	UAnimSequenceBase* Sequence = nullptr;

protected:
	virtual void Initialize(UAnimInstance* InAnimInstance) override;
	
	virtual FAnimNode_Base* GetCustomRootNode() override;

	virtual void GetCustomNodes(TArray<FAnimNode_Base*>& OutNodes) override;

private:
	FAnimNode_Base* RootNode = nullptr;
};

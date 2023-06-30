#pragma once
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimNode_Root.h"
#include "Animation/AnimNode_SequencePlayer.h"
#include "AnimNodes/AnimNode_TwoWayBlend.h"


class FAnimInstanceProxyPureCpp : public FAnimInstanceProxy
{
public:
	FAnimInstanceProxyPureCpp(UAnimInstance* Instance)
		: FAnimInstanceProxy(Instance)
	{
	}

protected:
	virtual void Initialize(UAnimInstance* InAnimInstance) override;
	
	virtual FAnimNode_Base* GetCustomRootNode() override;

	virtual void GetCustomNodes(TArray<FAnimNode_Base*>& OutNodes) override;

	virtual void Update(float DeltaSeconds) override;

private:
	UAnimSequenceBase* SequenceA = nullptr;
	UAnimSequenceBase* SequenceB = nullptr;
	FAnimNode_SequencePlayer A;
	FAnimNode_SequencePlayer B;
	FAnimNode_TwoWayBlend BlendSample;
	FAnimNode_Root InternalRootNode;
};

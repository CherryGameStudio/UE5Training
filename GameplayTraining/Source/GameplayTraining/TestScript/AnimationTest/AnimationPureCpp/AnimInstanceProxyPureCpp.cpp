#include "AnimInstanceProxyPureCpp.h"

#include "SkeletalMeshComponentPureCpp.h"
#include "Animation/AnimNode_Root.h"
#include "Animation/AnimNode_SequencePlayer.h"
#include "Animation/AnimNode_StateMachine.h"

void FAnimInstanceProxyPureCpp::Initialize(UAnimInstance* InAnimInstance)
{
	UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetAnimInstanceObject());
	USkeletalMeshComponentPureCpp* Mesh = Cast<USkeletalMeshComponentPureCpp>(AnimInstance->GetSkelMeshComponent());
	if (!Mesh)
	{
		return;
	}
	
	Sequence = Mesh->Temp;
	
	FAnimInstanceProxy::Initialize(InAnimInstance);
}

FAnimNode_Base* FAnimInstanceProxyPureCpp::GetCustomRootNode()
{
	if (!RootNode)
	{
		// FAnimNode_Root* Root = new FAnimNode_Root();
		// RootNode = Root;
		
		FAnimNode_SequencePlayer* Temp = new FAnimNode_SequencePlayer();
		Temp->SetSequence(Sequence);
		RootNode = Temp;
	}

	return RootNode;
}

void FAnimInstanceProxyPureCpp::GetCustomNodes(TArray<FAnimNode_Base*>& OutNodes)
{
	// todo 走跑
	// todo 跳

	// 站，走，跑状态机
	//FAnimNode_StateMachine* SM_Locomotion = new FAnimNode_StateMachine();
	
	OutNodes.Reset();
	OutNodes.Add(GetCustomRootNode());
}

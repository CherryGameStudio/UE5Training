#include "AnimInstanceProxyPureCpp.h"

#include "CharacterPureCpp.h"
#include "SkeletalMeshComponentPureCpp.h"

void FAnimInstanceProxyPureCpp::Initialize(UAnimInstance* InAnimInstance)
{
	UAnimInstance* AnimInstance = Cast<UAnimInstance>(GetAnimInstanceObject());
	USkeletalMeshComponent* Mesh = Cast<USkeletalMeshComponent>(AnimInstance->GetSkelMeshComponent());
	if (!Mesh)
	{
		return;
	}

	ACharacterPureCpp* Character = Cast<ACharacterPureCpp>(Mesh->GetOwner());
	if (!Character)
	{
		return;
	}
	
	SequenceA = Character->AnimA;
	SequenceB = Character->AnimB;
	
	FAnimInstanceProxy::Initialize(InAnimInstance);
}

FAnimNode_Base* FAnimInstanceProxyPureCpp::GetCustomRootNode()
{
	return &InternalRootNode;
}

void FAnimInstanceProxyPureCpp::GetCustomNodes(TArray<FAnimNode_Base*>& OutNodes)
{
	A.SetSequence(SequenceA);
	B.SetSequence(SequenceB);
	BlendSample.A.SetLinkNode(&A);
	BlendSample.B.SetLinkNode(&B);
	BlendSample.Alpha = 0;

	FAnimNode_Root* Root = static_cast<FAnimNode_Root*>(GetCustomRootNode());
	Root->Result.SetLinkNode(&BlendSample);
	
	OutNodes.Reset();
	OutNodes.Add(GetCustomRootNode());
}

void FAnimInstanceProxyPureCpp::Update(float DeltaSeconds)
{
	float Alpha = BlendSample.Alpha;
	if (Alpha >= 1)
	{
		BlendSample.Alpha = 0;
	}
	else
	{
		BlendSample.Alpha += DeltaSeconds / 10;
	}
}

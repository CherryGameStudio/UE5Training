#include "AnimNode_Custom.h"

void FAnimNode_Custom::Initialize_AnyThread(const FAnimationInitializeContext& Context)
{
	UE_LOG(LogTemp, Log, TEXT("FAnimNode_Custom::Initialize_AnyThread"));
	
	FAnimNode_Base::Initialize_AnyThread(Context);
}

void FAnimNode_Custom::CacheBones_AnyThread(const FAnimationCacheBonesContext& Context)
{
	UE_LOG(LogTemp, Log, TEXT("FAnimNode_Custom::CacheBones_AnyThread"));
	
	FAnimNode_Base::CacheBones_AnyThread(Context);
}

void FAnimNode_Custom::Update_AnyThread(const FAnimationUpdateContext& Context)
{
	UE_LOG(LogTemp, Log, TEXT("FAnimNode_Custom::Update_AnyThread"));
	
	FAnimNode_Base::Update_AnyThread(Context);
}

void FAnimNode_Custom::Evaluate_AnyThread(FPoseContext& Output)
{
	UE_LOG(LogTemp, Log, TEXT("FAnimNode_Custom::Evaluate_AnyThread"));
	
	FAnimNode_Base::Evaluate_AnyThread(Output);
}

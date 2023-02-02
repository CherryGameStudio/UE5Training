#include "AnimInstanceProxyPureCpp.h"

#include "Animation/AnimNode_Root.h"
#include "Animation/AnimNode_SequencePlayer.h"

FAnimNode_Base* FAnimInstanceProxyPureCpp::GetCustomRootNode()
{
	// 返回RootNode
	FAnimNode_Base* Root = nullptr;
	if (!RootNode)
	{
		Root = new FAnimNode_Root();
	}
	
	//return Root;

	FAnimNode_SequencePlayer* Temp = new FAnimNode_SequencePlayer();
	Temp->SetSequence(Sequence);
	return Temp;
}

void FAnimInstanceProxyPureCpp::GetCustomNodes(TArray<FAnimNode_Base*>& OutNodes)
{
	// 获得所有的Anim_Node用于初始化
	FAnimNode_Root* Root = static_cast<FAnimNode_Root*>(GetCustomRootNode());

	FAnimNode_SequencePlayer* Temp = new FAnimNode_SequencePlayer();
	Temp->SetSequence(Sequence);

	FPoseLink NewLink;
	NewLink.SetLinkNode(Temp);
	Root->Result = NewLink;

	OutNodes.Reset();
	//OutNodes.Add(Root);
	OutNodes.Add(GetCustomRootNode());
}

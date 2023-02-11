#pragma once
#include "Animation/AnimNodeBase.h"
#include "AnimNode_Custom.generated.h"

USTRUCT(BlueprintInternalUseOnly)
struct FAnimNode_Custom : public FAnimNode_Base
{
	GENERATED_USTRUCT_BODY()

public:
	/** 
	 * Called when the node first runs. If the node is inside a state machine or cached pose branch then this can be called multiple times. 
	 * This can be called on any thread.
	 * @param	Context		Context structure providing access to relevant data
	 */
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;

	/** 
	 * Called to cache any bones that this node needs to track (e.g. in a FBoneReference). 
	 * This is usually called at startup when LOD switches occur.
	 * This can be called on any thread.
	 * @param	Context		Context structure providing access to relevant data
	 */
	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;

	/** 
	 * Called to update the state of the graph relative to this node.
	 * Generally this should configure any weights (etc.) that could affect the poses that
	 * will need to be evaluated. This function is what usually executes EvaluateGraphExposedInputs.
	 * This can be called on any thread.
	 * @param	Context		Context structure providing access to relevant data
	 */
	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;

	/** 
	 * Called to evaluate local-space bones transforms according to the weights set up in Update().
	 * You should implement either Evaluate or EvaluateComponentSpace, but not both of these.
	 * This can be called on any thread.
	 * @param	Output		Output structure to write pose or curve data to. Also provides access to relevant data as a context.
	 */
	virtual void Evaluate_AnyThread(FPoseContext& Output) override;

private:
	
};

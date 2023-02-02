// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAnimInstance.h"

#include "Animation/AnimInstanceProxy.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "SkeletalMeshHelper/SkeletalMeshHelperComponent.h"

#if WITH_EDITORONLY_DATA
#include "Kismet2/KismetEditorUtilities.h"
#endif

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	USkeletalMeshHelperComponent* HelperComponent = GetHelperComponent();
	if (HelperComponent)
	{
		AnimDisplay = HelperComponent->AnimDisplay;

		// Simple Pose
		SimplePoseAsset = HelperComponent->SimplePoseAsset;
		SimplePoseTime = HelperComponent->SimplePoseTime;

		// Blend Pose
		BlendPoseAssetA = HelperComponent->BlendPoseAssetA;
		BlendPoseAssetB = HelperComponent->BlendPoseAssetB;
		BlendPoseTime = HelperComponent->BlendPoseTime;
		BlendPoseWidget = HelperComponent->BlendPoseWidget;

		// Simple Sequence
		SimpleSequenceAsset = HelperComponent->SimpleSequenceAsset;
		SimpleSequencePlayRate = HelperComponent->SimpleSequencePlayRate;
		
		// Blend Sequence
		BlendSequenceAssetA = HelperComponent->BlendSequenceAssetA;
		BlendSequenceAssetB = HelperComponent->BlendSequenceAssetB;
		BlendSequenceWidget = HelperComponent->BlendSequenceWidget;
		BlendSequencePlayRate = HelperComponent->BlendSequencePlayRate;

		// IK
		FootHeight = HelperComponent->FootHeight;
	}


	// IK
	// 1. 向地面做射线检测，算出脚底悬空的高度，算出脚底实际位置
	USkeletalMeshComponent* OwnerComp = GetOwningComponent();
	ACharacter* Character = Cast<ACharacter>(OwnerComp->GetOwner());

	if (!Character)
	{
		return;
	}
	
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(Character);
	
	FVector IKFootLoc = OwnerComp->GetSocketLocation("ball_l");
	IKFootLoc.Z = OwnerComp->GetSocketLocation("root").Z;
	FVector TraceStart = IKFootLoc + FVector(0,0,50);
	FVector TraceEnd = IKFootLoc - FVector(0,0,50);

	FHitResult HitResult;
	UWorld* World = GetWorld();
	UKismetSystemLibrary::LineTraceSingle(World, TraceStart, TraceEnd, (ETraceTypeQuery)ECC_Visibility, false, TArray<AActor*>{Character}, EDrawDebugTrace::ForDuration, HitResult, true);


	FVector TargetLocOffset = FVector::ZeroVector;
	FRotator TargetRotOffset = FRotator::ZeroRotator;
	if (Character->GetCharacterMovement()->IsWalkable(HitResult))
	{
		FVector ImpactPoint = HitResult.ImpactPoint;
		FVector ImpactNormal = HitResult.ImpactNormal;

		TargetLocOffset = (ImpactPoint + ImpactNormal * FootHeight) - (IKFootLoc + FVector(0, 0, FootHeight));
		
		TargetRotOffset.Pitch = -FMath::RadiansToDegrees(FMath::Atan2(ImpactNormal.X, ImpactNormal.Z));
		TargetRotOffset.Roll = FMath::RadiansToDegrees(FMath::Atan2(ImpactNormal.Y, ImpactNormal.Z));
	}
	else
	{
		//FootLocationOffset = FVector::ZeroVector;
	}

	CurFootLocOffset = FMath::VInterpTo(CurFootLocOffset, TargetLocOffset, DeltaSeconds, 30);
	CurFootRotOffset = FMath::RInterpTo(CurFootRotOffset, TargetRotOffset, DeltaSeconds, 30.0f);
}

USkeletalMeshHelperComponent* UMyAnimInstance::GetHelperComponent() const
{
	AActor* OwnerActor = GetOwningActor();
	if (!OwnerActor)
	{
		return nullptr;
	}

	USkeletalMeshHelperComponent* Component = Cast<USkeletalMeshHelperComponent>(OwnerActor->GetComponentByClass(USkeletalMeshHelperComponent::StaticClass()));

	return Component;
}


#if WITH_EDITOR
void UMyAnimInstance::DebugLogActiveSequencerPlayer()
{
	// TODO 要获得AnimNodeIndex需要修改源码中的FAnimNode_Base::GatherDebugData，在其中将FAnimNode_Base::GetNodeIndex()传入，获取需要GOTO AnimBP的AnimNode Index。
	FAnimInstanceProxy& Proxy = GetProxyOnGameThread<FAnimInstanceProxy>();
	FNodeDebugData NodeDebugData(this);
	Proxy.GatherDebugData(NodeDebugData);;
	TArray<FNodeDebugData::FFlattenedDebugData> FlattenedDebugDatas = NodeDebugData.GetFlattenedDebugData();
	for (FNodeDebugData::FFlattenedDebugData& Data : FlattenedDebugDatas)
	{
		if (Data.AbsoluteWeight > 0.001f)
		{
			auto FindValidNode = [&Data](const FString FindSubStr)
			{
				int32 NodeIndex = Data.DebugLine.Find(FindSubStr);
				if (NodeIndex >= 0)
				{
					return true;
				}
				else
				{
					return false;
				}
			};

			if (FindValidNode("AnimNode_SequencePlayer"))
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), *Data.DebugLine);
				break;
			}
				

			if (FindValidNode("AnimNode_SequenceEvaluator"))
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), *Data.DebugLine);
				break;
			}

			if (FindValidNode("AnimNode_BlendSpacePlayer"))
			{
				UE_LOG(LogTemp, Log, TEXT("%s"), *Data.DebugLine);
				break;
			}
		}	
	}
}

#endif

#if WITH_EDITORONLY_DATA
void UMyAnimInstance::GoToBPNode(int32 NodeIndex)
{

	FAnimInstanceProxy& Proxy = GetProxyOnGameThread<FAnimInstanceProxy>();
	UAnimBlueprint* AnimBlueprint = Proxy.GetAnimBlueprint();
	UAnimBlueprintGeneratedClass* AnimClass = AnimBlueprint ? AnimBlueprint->GetAnimBlueprintGeneratedClass() : nullptr;
	if (AnimClass)
	{
		const UEdGraphNode* GraphNode = AnimClass->GetVisualNodeFromNodePropertyIndex(NodeIndex);
		if (GraphNode)
		{
			FKismetEditorUtilities::BringKismetToFocusAttentionOnObject(GraphNode, /*bRequestRename=*/false);
		}
	}
}
#endif




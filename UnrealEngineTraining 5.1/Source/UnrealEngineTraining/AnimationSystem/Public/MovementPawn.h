// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovementPawn.generated.h"

UENUM(BlueprintType)
enum class ERotateType : uint8
{
	Quat	 	UMETA(DisplayName = "Quaternion"),
	Matrix		UMETA(DisplayName = "Matrix"),
	Count		UMETA(Hidden),
};

UCLASS()
class UNREALENGINETRAINING_API AMovementPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMovementPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	//恢复初始Transform信息
	UFUNCTION(Category = "Cherry", CallInEditor)
	void ResetTransform() const;

	//执行位移
	UFUNCTION(Category = "Cherry", CallInEditor)
	void ApplyDisplacementOffset();

	//执行绕着旋转轴自旋操作
	UFUNCTION(Category = "Cherry", CallInEditor)
	void ApplySelfRotation();

	//通过穿过某点的旋转轴旋转物体坐标  
	UFUNCTION(Category = "Cherry", CallInEditor)
	void ApplyRotatorVector();
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE float GetMyVelocity() const
	{
		return  InVelocity;
	}

private:
	void FollowPlayer(float DeltaTime);
	
public:
	UPROPERTY(VisibleAnywhere, Category = "Cherry", BlueprintReadOnly)
	USkeletalMeshComponent* Mesh;

	//位移速度
	UPROPERTY(EditAnywhere, Category = "Cherry|Common")
	float Velocity;

	UPROPERTY(EditAnywhere, Category = "Cherry|PlayerFollow")
	bool bFollow;

	UPROPERTY(EditAnywhere, Category = "Cherry|PlayerFollow")
	FVector HeadVector;

	UPROPERTY(EditAnywhere, Category = "Cherry|PlayerFollow")
	float MaxDistance;

	UPROPERTY(EditAnywhere, Category = "Cherry|PlayerFollow")
	float MinDistance;

	//是否允许在X轴上有所运动
	UPROPERTY(EditAnywhere, Category = "Cherry|PlayerFollow")
    bool bMoveInZAxis; 
    
	UPROPERTY(EditAnywhere, Category = "Cherry|PlayerFollow|Rotation")
	bool bFrozenX;

	UPROPERTY(EditAnywhere, Category = "Cherry|PlayerFollow|Rotation")
	bool bFrozenY;

	UPROPERTY(EditAnywhere, Category = "Cherry|PlayerFollow|Rotation")
	bool bFrozenZ;

	//位移偏量
	UPROPERTY(EditAnywhere, Category = "Cherry|Displacement")
	FVector DisplacementOffset;

	UPROPERTY(EditAnywhere, Category = "Cherry|Displacement")
	FVector DisplacementLocation;

	//是否使用位移偏量，false：使用TargetLocation
	UPROPERTY(EditAnywhere, Category = "Cherry|Displacement")
	bool bUseDisplacementOffset;

	UPROPERTY(EditAnywhere, Category = "Cherry|Rotation|Common")
	ERotateType RotateType;

	//是否反向旋转
	UPROPERTY(EditAnywhere, Category = "Cherry|Rotation|Common")
	bool bInverse;
	
	//欧拉角旋转相关
	UPROPERTY(EditAnywhere, Category = "Cherry|Rotation|Euler")
	FRotator EulerRotator;

	//矩阵旋转

	//四元数旋转
	UPROPERTY(EditAnywhere, Category = "Cherry|Rotation|Quat")
	FVector QuatAxis;

	UPROPERTY(EditAnywhere, Category = "Cherry|Rotation|Quat")
	float Angle;

	UPROPERTY(EditAnywhere, Category = "Cherry|Rotation|Quat")
	FVector RotatorPoint;

private:
	float InVelocity;

	FVector DefaultLocation;
	FRotator DefaultRotation;
	FVector DefaultScale;

	//是否处于运动中
	uint32 bInMovement : 1;
	uint32 bInRotation : 1;

	//速度方向
	FVector VelocityDirectory;

	FVector TargetLocation;
	FRotator TargetRotation;

	float TotalDegree;

	bool bFollowing;
};

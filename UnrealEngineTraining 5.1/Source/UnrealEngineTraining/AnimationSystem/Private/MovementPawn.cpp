// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealEngineTraining/AnimationSystem/Public/MovementPawn.h"

#include "Kismet/GameplayStatics.h"
#include "UnrealEngineTraining/AnimationSystem/Public/Character/PlayerCharacter.h"


// Sets default values
AMovementPawn::AMovementPawn()
{
	
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("MovementPawnMesh");
	RootComponent = Mesh;
	
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bInMovement = 0;
	bInRotation = 0;
	
	DefaultLocation = GetActorLocation();
	DefaultRotation = GetActorRotation();
	DefaultScale = GetActorScale();
}

// Called when the game starts or when spawned
void AMovementPawn::BeginPlay()
{
	Super::BeginPlay();

	DefaultLocation = GetActorLocation();
	DefaultRotation = GetActorRotation();
	DefaultScale = GetActorScale();
}

// Called every frame
void AMovementPawn::Tick(float DeltaTime)
{
	if (bFollow)
	{
		FollowPlayer(DeltaTime);
	}
	else if (bInMovement)
	{
		//计算方向
		FVector Direction = (TargetLocation - GetActorLocation()).GetSafeNormal();

		if (bInRotation)
		{
			//旋转
			FVector vec1 = HeadVector;
			FQuat quat1 = GetActorRotation().Quaternion();
			FVector vec2 = quat1.RotateVector(vec1).GetSafeNormal();//初始伞头矢量方向
			FVector vec3 = Direction;//目标伞头矢量方向
			UE_LOG(LogTemp, Warning, TEXT("VecStart: %s	VecTarget: %s"), *vec2.ToString(), *vec3.ToString());
			
			//四元数方法
			FVector axis = FVector::CrossProduct(vec2, vec3).GetSafeNormal();//旋转轴是两个向量的叉乘
			float rad = FMath::Acos(FVector::DotProduct(vec2, vec3) /
				(vec2.Size() * vec3.Size()));//FMath::Acos得到的是以弧度为单位的结果
			FQuat quat2 = FQuat(axis, rad);
			
			SetActorRotation(quat1 * quat2);
			bInRotation = false;
		}
		
		//平移
		FVector DeltaOffset = Direction * Velocity;
		SetActorLocation(GetActorLocation() + DeltaOffset);

		
		FVector NewDirectory = (TargetLocation - GetActorLocation()).GetSafeNormal();
		//方向相反
		if ((Direction | NewDirectory) <= .0f)
		{
			bInMovement = false;
			bInRotation = false;
			UE_LOG(LogTemp, Warning, TEXT("位移结束"));
		}	
	}
	
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMovementPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMovementPawn::ResetTransform() const
{
	RootComponent->SetRelativeLocation(DefaultLocation);
	RootComponent->SetRelativeRotation(DefaultRotation);
	RootComponent->SetRelativeScale3D(DefaultScale);
}

void AMovementPawn::ApplyDisplacementOffset()
{
	if (bInMovement)
	{
		return;
	}
	
	if (bUseDisplacementOffset)
	{
		TargetLocation = RootComponent->GetRelativeLocation() + DisplacementOffset; 
	}
	else
	{
		TargetLocation = DisplacementLocation;
	}

	
	TotalDegree = 0;
	bInMovement = 1;
	bInRotation = 1;
	UE_LOG(LogTemp, Warning, TEXT("位移开始"));
}

void AMovementPawn::ApplySelfRotation()
{
	if (RotateType == ERotateType::Quat)
	{
		//Quat
		FQuat DeltaQuat(QuatAxis, FMath::DegreesToRadians(Angle));
		FQuat OldQuat = GetActorQuat();
		if (bInverse)
		{
			DeltaQuat = DeltaQuat.Inverse();
		}
		SetActorRotation(OldQuat * DeltaQuat);
	}
	else if (RotateType == ERotateType::Matrix)
	{
		FRotationMatrix OldMatrix(GetActorRotation());
		const FQuat DeltaQuat(QuatAxis, FMath::DegreesToRadians(Angle));
		FMatrix DeltaMatrix = FRotationMatrix::Make(DeltaQuat);
		if (bInverse)
		{
			DeltaMatrix = DeltaMatrix.Inverse();
		}
		SetActorRotation((OldMatrix * DeltaMatrix).ToQuat());
	}
}

void AMovementPawn::ApplyRotatorVector()
{
	if (RotateType == ERotateType::Quat)
	{
		FQuat Quat(QuatAxis ,FMath::DegreesToRadians(Angle));
		//RotateVector: V' = P * V * P^(-1)
		FVector VecStart = GetActorLocation() - RotatorPoint;
		FVector VectorEnd;
		if (!bInverse)
		{
			VectorEnd = Quat.RotateVector(VecStart);
		}
		else
		{
			Quat = Quat.Inverse();
			VectorEnd = Quat.RotateVector(VecStart);
		}
		SetActorLocation(RotatorPoint + VectorEnd);
	}
	else if (RotateType == ERotateType::Matrix)
	{
		FQuat Quat(QuatAxis ,FMath::DegreesToRadians(Angle));
		FMatrix DeltaMatrix = FRotationMatrix::Make(Quat);
		//RotateVector: V' = P * V * P^(-1)
		FVector VecStart = GetActorLocation() - RotatorPoint;
		FVector VectorEnd;
		if (!bInverse)
		{
			VectorEnd = DeltaMatrix.TransformVector(VecStart);
		}
		else
		{
			VectorEnd = DeltaMatrix.InverseTransformVector(VecStart);
		}
		SetActorLocation(RotatorPoint + VectorEnd);
	}
}

void AMovementPawn::FollowPlayer(float DeltaTime)
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (Player)
	{
		FVector PlayerLocation = Player->GetActorLocation();
		FVector DistanceVector = PlayerLocation - GetActorLocation();
		float Distance = DistanceVector.Length();
		
		//大于最大响应距离就不跟随了
		if (Distance > MaxDistance)
		{
			InVelocity = 0;
			return;
		}

		FVector Direction = DistanceVector.GetSafeNormal();
		FVector DeltaOffset;
		//小于最小跟随距离要反向远离
		if (Distance < MinDistance)
		{
			DeltaOffset = -Direction * Velocity * DeltaTime;
			InVelocity = -Velocity;
		}
		else
		{
			DeltaOffset = Direction * Velocity * DeltaTime;
			InVelocity = Velocity;
		}

		if (!bMoveInZAxis)
		{
			DeltaOffset.Z = 0;
		}

		
		const bool bMove = FMath::Abs(Distance - MinDistance) > 25.0f;
		UE_LOG(LogTemp, Warning, TEXT("Distance - MinDistance: %f, InVelocity: %f"), Distance - MinDistance, InVelocity)
		
		FVector UmbrellaHeadVector = HeadVector;//指定头方向
		FQuat OldQuat = GetActorRotation().Quaternion();
		FVector StartUmbrellaHeadVector = OldQuat.RotateVector(UmbrellaHeadVector);//初始头方向
		FQuat DeltaQuat(
			FVector::CrossProduct(StartUmbrellaHeadVector, Direction),
			FMath::Acos(FVector::DotProduct(StartUmbrellaHeadVector, Direction)));

		if (bFrozenX)
		{
			DeltaQuat.X = 0;
		}
		if (bFrozenY)
		{
			DeltaQuat.Y = 0;
		}
		if (bFrozenZ)
		{
			DeltaQuat.Z = 0;
		}
		DeltaQuat.Normalize();
		//四元数相乘必须是Delta * Old 不能反向：TODO 为什么
		FQuat TerminalQuat = DeltaQuat * OldQuat;
		SetActorRotation(TerminalQuat);
		//SetActorRotation(OldQuat.Rotator() + DeltaQuat.Rotator());   //直接加欧拉角貌似也行，但不建议

		if (!bMove)
		{
			InVelocity = 0;
			return;
		}
		SetActorLocation(GetActorLocation() + DeltaOffset);
	}
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "VectorActor.h"


// Sets default values
AVectorActor::AVectorActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
}

// Called when the game starts or when spawned
void AVectorActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVectorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldMove)
	{
		StaticMesh->AddRelativeLocation(Vector1 * DeltaTime);
	}
}

void AVectorActor::ExplainVector() const
{
	UE_LOG(LogTemp, Log, TEXT("--------ExplainVector Begin--------"));
	FVector LocalVector1 = Vector1;
	UE_LOG(LogTemp, Log, TEXT("目标Vector值为：%s。"), *LocalVector1.ToString());


	UE_LOG(LogTemp, Log, TEXT("下面是Vector获得属性的函数"));
	UE_LOG(LogTemp, Log, TEXT("GetMax()：%f。"),		LocalVector1.GetMax());
	UE_LOG(LogTemp, Log, TEXT("GetAbsMax()：%f。"),		LocalVector1.GetAbsMax());
	UE_LOG(LogTemp, Log, TEXT("GetMin()：%f。"),		LocalVector1.GetMin());
	UE_LOG(LogTemp, Log, TEXT("GetAbsMin()：%f。"),		LocalVector1.GetAbsMin());
	UE_LOG(LogTemp, Log, TEXT("GetAbs()：%s。"),		*LocalVector1.GetAbs().ToString());
	UE_LOG(LogTemp, Log, TEXT("Size()：%f。"),			LocalVector1.Size());					// 获得向量长度
	UE_LOG(LogTemp, Log, TEXT("Length()：%f。"),		LocalVector1.Length());					// 等同于::Size
	UE_LOG(LogTemp, Log, TEXT("SizeSquared()：%f。"),	LocalVector1.SizeSquared());
	UE_LOG(LogTemp, Log, TEXT("SquaredLength()：%f。"),	LocalVector1.SquaredLength());
	UE_LOG(LogTemp, Log, TEXT("Size2D()：%f。"),		LocalVector1.Size2D());					// 获得2维向量长度
	UE_LOG(LogTemp, Log, TEXT("SizeSquared2D()：%f。"),	LocalVector1.SizeSquared2D());
	UE_LOG(LogTemp, Log, TEXT("IsNearlyZero()：%s。"),	LocalVector1.IsNearlyZero() ? TEXT("true") : TEXT("false"));
	UE_LOG(LogTemp, Log, TEXT("IsZero()：%s。"),		LocalVector1.IsZero() ? TEXT("true") : TEXT("false"));
	UE_LOG(LogTemp, Log, TEXT("IsUnit()：%s。"),		LocalVector1.IsUnit() ? TEXT("true") : TEXT("false"));

	// 作为向量
	UE_LOG(LogTemp, Log, TEXT("IsNormalized()：%s。"),	LocalVector1.IsNormalized() ? TEXT("true") : TEXT("false"));
	{
		// 归一化
		FVector TempVector = LocalVector1;
		TempVector.Normalize();
		UE_LOG(LogTemp, Log, TEXT("Normalize()：%s。"),	*TempVector.ToString());
	}
	UE_LOG(LogTemp, Log, TEXT("GetUnsafeNormal()：%s。"),	*LocalVector1.GetUnsafeNormal().ToString());
	UE_LOG(LogTemp, Log, TEXT("GetSafeNormal()：%s。"),		*LocalVector1.GetSafeNormal().ToString());
	UE_LOG(LogTemp, Log, TEXT("GetSafeNormal2D()：%s。"),	*LocalVector1.GetSafeNormal2D().ToString());
	UE_LOG(LogTemp, Log, TEXT("GetUnsafeNormal2D()：%s。"),	*LocalVector1.GetUnsafeNormal2D().ToString());
	{
		// 转换为方向向量和长度
		FVector TempVector = LocalVector1;
		float Length = 0;
		LocalVector1.ToDirectionAndLength(TempVector, Length);
		UE_LOG(LogTemp, Log, TEXT("ToDirectionAndLength(), OutDir: %s, OutLength: %f。"), *TempVector.ToString(), Length);
	}
	UE_LOG(LogTemp, Log, TEXT("GetSignVector()：%s。"),	*LocalVector1.GetSignVector().ToString());		// 获得向量前面的符号(正负号)
	UE_LOG(LogTemp, Log, TEXT("Projection()：%s。"),	*LocalVector1.Projection().ToString());			// TODO 不太懂这个自身投影的意义
	
	{
		// TODO Clamp   BoundToCube
	}
	
	// 两个Vector之间的操作
	FVector LocalVector2 = Vector2;
	// 点乘
	UE_LOG(LogTemp, Log, TEXT("operator * ：%f。"),	LocalVector1 | LocalVector2);
	UE_LOG(LogTemp, Log, TEXT("FVector::DotProduct ：%f。"),	FVector::DotProduct(LocalVector1, LocalVector2));

	// 叉乘
	UE_LOG(LogTemp, Log, TEXT("operator ^ ：%s。"),	*(LocalVector1 ^ LocalVector2).ToString());
	UE_LOG(LogTemp, Log, TEXT("FVector::CrossProduct ：%s。"),	*FVector::CrossProduct(LocalVector1, LocalVector2).ToString());
  
	UE_LOG(LogTemp, Log, TEXT("--------ExplainVector End--------"));
}


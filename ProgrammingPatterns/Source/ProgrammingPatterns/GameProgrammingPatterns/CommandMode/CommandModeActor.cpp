// Fill out your copyright notice in the Description page of Project Settings.


#include "CommandModeActor.h"

#include "EasyCommand.h"
#include "FunctionCommand.h"

// Sets default values
ACommandModeActor::ACommandModeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACommandModeActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACommandModeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACommandModeActor::EC_DoOnce()
{
	ICommand* NewCommand = new TransformCommand(this, EC_TargetTransform);
	bool bSucceed = NewCommand->TryExecute();

	if (bSucceed)
	{
		EC_Stack.Push(NewCommand);
	}
}

void ACommandModeActor::EC_UnDo()
{
	if (EC_Stack.Num() > 0)
	{
		ICommand* Command = EC_Stack.Pop();
		Command->UnDo();
		delete Command;
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("没有可以撤销的操作"));
	}
}

void ACommandModeActor::FC_DoOnce()
{
	// TODO 模板有问题先忽略
	
	// MyTFunction<void(AActor*,FTransform)> Func = [](AActor* Actor, FTransform Trans)
	// {
	// 	Actor->SetActorTransform(Trans);
	// 	UE_LOG(LogTemp, Log, TEXT("FC_DoOnce"));
	// };

	//Func(this, FC_TargetTransform);
}


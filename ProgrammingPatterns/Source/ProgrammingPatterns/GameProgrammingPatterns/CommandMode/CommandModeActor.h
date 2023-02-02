// Fill out your copyright notice in the Description page of Project Settings.

/**
 * 命令模式
 * Easy Command：实现了简单的命令调度和撤销功能，通过ICommand将命令对象化并使得发出命令和执行命令责任分割开。
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CommandModeActor.generated.h"

UCLASS()
class PROGRAMMINGPATTERNS_API ACommandModeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACommandModeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Easy Command
public:
	UPROPERTY(EditAnywhere, Category = "Easy Command")
	FTransform EC_TargetTransform;

	UFUNCTION(CallInEditor, Category = "Easy Command")
	void EC_DoOnce();

	UFUNCTION(CallInEditor, Category = "Easy Command")
	void EC_UnDo();
private:
	TArray<class ICommand*> EC_Stack;

	//My Function Command
public:
	UPROPERTY(EditAnywhere, Category = "My Function Command")
	FTransform FC_TargetTransform;

	UFUNCTION(CallInEditor, Category = "My Function Command")
	void FC_DoOnce();
};

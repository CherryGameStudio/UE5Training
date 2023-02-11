// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "GameplayInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FGameplayInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UInputAction> InputAction;

	UPROPERTY(EditDefaultsOnly)
	TArray<ETriggerEvent> TriggerEvents;

	UPROPERTY(EditDefaultsOnly)
	bool bBindUFunction;

	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "bBindUFunction"))
	FName UFunctionName;
};

UCLASS(BlueprintType, Const)
class GAMEPLAYTRAINING_API UGameplayInputActionConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<FGameplayInputAction> InputActions;
};

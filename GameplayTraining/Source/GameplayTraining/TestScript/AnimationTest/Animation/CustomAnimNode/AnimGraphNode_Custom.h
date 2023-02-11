// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimGraphNode_Base.h"
#include "AnimNode_Custom.h"
#include "AnimGraphNode_Custom.generated.h"

/**
 * 
 */
UCLASS()
class GAMEPLAYTRAINING_API UAnimGraphNode_Custom : public UAnimGraphNode_Base
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category=Settings)
	FAnimNode_Custom Node;

	// UEdGraphNode interface
	virtual FText GetTooltipText() const override;
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	// End of UEdGraphNode interface
};

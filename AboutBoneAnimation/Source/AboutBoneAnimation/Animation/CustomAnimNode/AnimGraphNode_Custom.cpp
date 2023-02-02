// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimGraphNode_Custom.h"

FText UAnimGraphNode_Custom::GetTooltipText() const
{
	return Super::GetTooltipText();
}

FText UAnimGraphNode_Custom::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return Super::GetNodeTitle(TitleType);
}

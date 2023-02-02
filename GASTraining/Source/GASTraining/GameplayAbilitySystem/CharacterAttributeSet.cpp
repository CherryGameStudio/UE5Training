// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterAttributeSet.h"

#include "GASTraining/TP_ThirdPerson/TP_ThirdPersonCharacter.h"
#include "Net/UnrealNetwork.h"

UCharacterAttributeSet::UCharacterAttributeSet()
{
	MaxHealth = FGameplayAttributeData(100);
	Health = FGameplayAttributeData(100);
	MaxMana = FGameplayAttributeData(50);
	Mana = FGameplayAttributeData(50);
}

void UCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UCharacterAttributeSet, Health);
	DOREPLIFETIME(UCharacterAttributeSet, MaxHealth);
	DOREPLIFETIME(UCharacterAttributeSet, Mana);
	DOREPLIFETIME(UCharacterAttributeSet, MaxMana);
}

void UCharacterAttributeSet::OnRep_Health(FGameplayAttributeData OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Health, OldValue);
	ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(GetOwningActor());
	if (MyCharacter)
	{
		MyCharacter->OnAttributeSetUpdate();
	}
}

void UCharacterAttributeSet::OnRep_MaxHealth(FGameplayAttributeData OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, MaxHealth, OldValue);
	ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(GetOwningActor());
	if (MyCharacter)
	{
		MyCharacter->OnAttributeSetUpdate();
	}
}

void UCharacterAttributeSet::OnRep_Mana(FGameplayAttributeData OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, Mana, OldValue);
	ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(GetOwningActor());
	if (MyCharacter)
	{
		MyCharacter->OnAttributeSetUpdate();
	}
}

void UCharacterAttributeSet::OnRep_MaxMana(FGameplayAttributeData OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UCharacterAttributeSet, MaxMana, OldValue);
	ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(GetOwningActor());
	if (MyCharacter)
	{
		MyCharacter->OnAttributeSetUpdate();
	}
}

void UCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	ATP_ThirdPersonCharacter* MyCharacter = Cast<ATP_ThirdPersonCharacter>(GetOwningActor());
	if (MyCharacter)
	{
		MyCharacter->OnAttributeSetUpdate();
	}
}

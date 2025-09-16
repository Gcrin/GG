// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GGShieldSet.h"

UGGShieldSet::UGGShieldSet()
	: Shield(0.0f)
	, MaxShield(0.0f)
{
}

void UGGShieldSet::OnRep_Shield(const FGameplayAttributeData& OldValue)
{
}

void UGGShieldSet::OnRep_MaxShield(const FGameplayAttributeData& OldValue)
{
}

bool UGGShieldSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	return Super::PreGameplayEffectExecute(Data);
}

void UGGShieldSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
}

void UGGShieldSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
}

void UGGShieldSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
}

void UGGShieldSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UGGShieldSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
}

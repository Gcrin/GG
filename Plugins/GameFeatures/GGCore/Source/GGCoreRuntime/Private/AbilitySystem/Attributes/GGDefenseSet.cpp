// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GGDefenseSet.h"

#include "Net/UnrealNetwork.h"

UGGDefenseSet::UGGDefenseSet()
	: PhysicalDamageReduction(0.0f)
	, MagicDamageReduction(0.0f)
	, FlatDamageReduction(0.0f)
{
}

void UGGDefenseSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGGDefenseSet, PhysicalDamageReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGDefenseSet, MagicDamageReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGDefenseSet, FlatDamageReduction, COND_None, REPNOTIFY_Always);
}

void UGGDefenseSet::OnRep_PhysicalDamageReduction(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGDefenseSet, PhysicalDamageReduction, OldValue);
	
	OnPhysicalDamageReductionChanged.Broadcast(nullptr, nullptr, nullptr, GetPhysicalDamageReduction() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetPhysicalDamageReduction());
}

void UGGDefenseSet::OnRep_MagicDamageReduction(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGDefenseSet, MagicDamageReduction, OldValue);
	
	OnMagicDamageReductionChanged.Broadcast(nullptr, nullptr, nullptr, GetMagicDamageReduction() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetMagicDamageReduction());
}

void UGGDefenseSet::OnRep_FlatDamageReduction(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGDefenseSet, FlatDamageReduction, OldValue);

	OnFlatDamageReductionChanged.Broadcast(nullptr, nullptr, nullptr, GetFlatDamageReduction() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetFlatDamageReduction());
}

void UGGDefenseSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	
	ClampAttribute(Attribute, NewValue);
}

void UGGDefenseSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	ClampAttribute(Attribute, NewValue);
}

void UGGDefenseSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetPhysicalDamageReductionAttribute() || Attribute == GetMagicDamageReductionAttribute())
	{
		NewValue = FMath::Min(NewValue, 0.85f);
	}
	else if (Attribute == GetFlatDamageReductionAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

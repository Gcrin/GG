// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GGDefenseSet.h"

#include "Net/UnrealNetwork.h"

UGGDefenseSet::UGGDefenseSet()
	: PhysicalDamageReduction(0.0f)
	, MagicDamageReduction(0.0f)
	, PhysicalDamageAbsorption(0.0f)
	, MagicDamageAbsorption(0.0f)
{
}

void UGGDefenseSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGGDefenseSet, PhysicalDamageReduction, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGDefenseSet, MagicDamageReduction, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGDefenseSet, PhysicalDamageAbsorption, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGDefenseSet, MagicDamageAbsorption, COND_OwnerOnly, REPNOTIFY_Always);
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

void UGGDefenseSet::OnRep_PhysicalDamageAbsorption(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGDefenseSet, PhysicalDamageAbsorption, OldValue);
	
	OnPhysicalDamageAbsorptionChanged.Broadcast(nullptr, nullptr, nullptr, GetPhysicalDamageAbsorption() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetPhysicalDamageAbsorption());
}

void UGGDefenseSet::OnRep_MagicDamageAbsorption(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGDefenseSet, MagicDamageAbsorption, OldValue);
	
	OnMagicDamageAbsorptionChanged.Broadcast(nullptr, nullptr, nullptr, GetMagicDamageAbsorption() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetMagicDamageAbsorption());
}

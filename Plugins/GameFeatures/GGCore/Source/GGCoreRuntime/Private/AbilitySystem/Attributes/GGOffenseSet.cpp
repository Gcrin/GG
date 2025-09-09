// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GGOffenseSet.h"

#include "Net/UnrealNetwork.h"

UGGOffenseSet::UGGOffenseSet()
	: CritChance(0.0f)
	, CritDamage(200.0f)
	, PhysicalDamageAmp(0.0f)
	, MagicDamageAmp(0.0f)
	, AttackSpeed(1.0f)
	, PhysicalPenetration(0.0f)
	, MagicPenetration(0.0f)
	, CastSpeed(1.0f)
{
}

void UGGOffenseSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGGOffenseSet, AttackSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGOffenseSet, CastSpeed, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UGGOffenseSet, CritChance, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGOffenseSet, CritDamage, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGOffenseSet, PhysicalDamageAmp, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGOffenseSet, MagicDamageAmp, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGOffenseSet, PhysicalPenetration, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGOffenseSet, MagicPenetration, COND_OwnerOnly, REPNOTIFY_Always);
}

void UGGOffenseSet::OnRep_CritChance(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGOffenseSet, CritChance, OldValue);

	OnCritChanceChanged.Broadcast(nullptr, nullptr, nullptr, GetCritChance() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetCritChance());
}

void UGGOffenseSet::OnRep_CritDamage(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGOffenseSet, CritDamage, OldValue);

	OnCritDamageChanged.Broadcast(nullptr, nullptr, nullptr, GetCritDamage() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetCritDamage());
}

void UGGOffenseSet::OnRep_PhysicalDamageAmp(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGOffenseSet, PhysicalDamageAmp, OldValue);

	OnPhysicalDamageAmpChanged.Broadcast(nullptr, nullptr, nullptr, GetPhysicalDamageAmp() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetPhysicalDamageAmp());
}

void UGGOffenseSet::OnRep_MagicDamageAmp(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGOffenseSet, MagicDamageAmp, OldValue);
	
	OnMagicDamageAmpChanged.Broadcast(nullptr, nullptr, nullptr, GetMagicDamageAmp() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetMagicDamageAmp());
}

void UGGOffenseSet::OnRep_AttackSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGOffenseSet, AttackSpeed, OldValue);
	
	OnAttackSpeedChanged.Broadcast(nullptr, nullptr, nullptr, GetAttackSpeed() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetAttackSpeed());
}

void UGGOffenseSet::OnRep_PhysicalPenetration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGOffenseSet, PhysicalPenetration, OldValue);
	
	OnPhysicalPenetrationChanged.Broadcast(nullptr, nullptr, nullptr, GetPhysicalPenetration() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetPhysicalPenetration());
}

void UGGOffenseSet::OnRep_MagicPenetration(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGOffenseSet, MagicPenetration, OldValue);
	
	OnMagicPenetrationChanged.Broadcast(nullptr, nullptr, nullptr, GetMagicPenetration() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetMagicPenetration());
}

void UGGOffenseSet::OnRep_CastSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGOffenseSet, CastSpeed, OldValue);
	
	OnCastSpeedChanged.Broadcast(nullptr, nullptr, nullptr, GetCastSpeed() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetCastSpeed());
}

void UGGOffenseSet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UGGOffenseSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UGGOffenseSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetAttackSpeedAttribute() || Attribute == GetCastSpeedAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.2f);
	}
	else if (Attribute == GetCritChanceAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 100.0f);
	}
	else if (Attribute == GetPhysicalPenetrationAttribute() || Attribute == GetMagicPenetrationAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, 100.0f);
	}
}

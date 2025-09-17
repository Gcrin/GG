// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GGUtilitySet.h"

#include "Net/UnrealNetwork.h"

UGGUtilitySet::UGGUtilitySet()
	: StaminaRegen(0.0f)
	, StaminaRegenPercent(0.0f)
	, ManaRegen(0.0f)
	, ManaRegenPercent(0.0f)
	, HealthRegen(0.0f)
	, HealthRegenPercent(0.0f)
	, MoveSpeed(600.0f)
	, CooldownReduction(0.0f)
	, PhysicalLifeSteal(0.0f)
	, MagicLifeSteal(0.0f)
{
}

void UGGUtilitySet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, MoveSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, StaminaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, StaminaRegenPercent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, ManaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, ManaRegenPercent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, HealthRegenPercent, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, CooldownReduction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, PhysicalLifeSteal, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, MagicLifeSteal, COND_None, REPNOTIFY_Always);
}

void UGGUtilitySet::OnRep_StaminaRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, StaminaRegen, OldValue);

	OnStaminaRegenChanged.Broadcast(nullptr, nullptr, nullptr, GetStaminaRegen() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetStaminaRegen());
}

void UGGUtilitySet::OnRep_StaminaRegenPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, StaminaRegenPercent, OldValue);

	OnStaminaRegenPercentChanged.Broadcast(nullptr, nullptr, nullptr, GetStaminaRegenPercent() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetStaminaRegenPercent());
}

void UGGUtilitySet::OnRep_ManaRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, ManaRegen, OldValue);

	OnManaRegenChanged.Broadcast(nullptr, nullptr, nullptr, GetManaRegen() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetManaRegen());
}

void UGGUtilitySet::OnRep_ManaRegenPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, ManaRegenPercent, OldValue);

	OnManaRegenPercentChanged.Broadcast(nullptr, nullptr, nullptr, GetManaRegenPercent() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetManaRegenPercent());
}

void UGGUtilitySet::OnRep_HealthRegen(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, HealthRegen, OldValue);

	OnHealthRegenChanged.Broadcast(nullptr, nullptr, nullptr, GetHealthRegen() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetHealthRegen());
}

void UGGUtilitySet::OnRep_HealthRegenPercent(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, HealthRegenPercent, OldValue);

	OnHealthRegenPercentChanged.Broadcast(nullptr, nullptr, nullptr, GetHealthRegenPercent() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetHealthRegenPercent());
}

void UGGUtilitySet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, MoveSpeed, OldValue);

	OnMoveSpeedChanged.Broadcast(nullptr, nullptr, nullptr, GetMoveSpeed() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetMoveSpeed());
}

void UGGUtilitySet::OnRep_CooldownReduction(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, CooldownReduction, OldValue);

	OnCooldownReductionChanged.Broadcast(nullptr, nullptr, nullptr, GetCooldownReduction() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetCooldownReduction());
}

void UGGUtilitySet::OnRep_PhysicalLifeSteal(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, PhysicalLifeSteal, OldValue);

	OnPhysicalLifeStealChanged.Broadcast(nullptr, nullptr, nullptr, GetPhysicalLifeSteal() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetPhysicalLifeSteal());
}

void UGGUtilitySet::OnRep_MagicLifeSteal(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, MagicLifeSteal, OldValue);

	OnMagicLifeStealChanged.Broadcast(nullptr, nullptr, nullptr, GetMagicLifeSteal() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetMagicLifeSteal());
}

void UGGUtilitySet::PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	
	ClampAttribute(Attribute, NewValue);
}

void UGGUtilitySet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UGGUtilitySet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetMoveSpeedAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
	else if (Attribute == GetPhysicalLifeStealAttribute() || Attribute == GetMagicLifeStealAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

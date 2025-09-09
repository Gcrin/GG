// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GGUtilitySet.h"

#include "Net/UnrealNetwork.h"

UGGUtilitySet::UGGUtilitySet()
	: StaminaRegenRate(0.0f)
	, ManaRegenRate(0.0f)
	, HealthRegenRate(0.0f)
	, MoveSpeed(600.0f)
	, CooldownReduction(0.0f)
{
}

void UGGUtilitySet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, MoveSpeed, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, StaminaRegenRate, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, ManaRegenRate, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, HealthRegenRate, COND_OwnerOnly, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UGGUtilitySet, CooldownReduction, COND_OwnerOnly, REPNOTIFY_Always);
}

void UGGUtilitySet::OnRep_StaminaRegenRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, StaminaRegenRate, OldValue);

	OnStaminaRegenRateChanged.Broadcast(nullptr, nullptr, nullptr, GetStaminaRegenRate() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetStaminaRegenRate());
}

void UGGUtilitySet::OnRep_ManaRegenRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, ManaRegenRate, OldValue);

	OnManaRegenRateChanged.Broadcast(nullptr, nullptr, nullptr, GetManaRegenRate() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetManaRegenRate());
}

void UGGUtilitySet::OnRep_HealthRegenRate(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, HealthRegenRate, OldValue);

	OnHealthRegenRateChanged.Broadcast(nullptr, nullptr, nullptr, GetHealthRegenRate() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetHealthRegenRate());
}

void UGGUtilitySet::OnRep_MoveSpeed(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, CooldownReduction, OldValue);

	OnCooldownReductionChanged.Broadcast(nullptr, nullptr, nullptr, GetCooldownReduction() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetCooldownReduction());
}

void UGGUtilitySet::OnRep_CooldownReduction(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGUtilitySet, MoveSpeed, OldValue);

	OnMoveSpeedChanged.Broadcast(nullptr, nullptr, nullptr, GetMoveSpeed() - OldValue.GetCurrentValue(), OldValue.GetCurrentValue(), GetMoveSpeed());
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Attributes/GGShieldSet.h"

#include "GameplayEffectExtension.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UGGShieldSet::UGGShieldSet()
	: Shield(0.0f)
{
	ShieldBeforeAttributeChange = 0.0f;
}

void UGGShieldSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UGGShieldSet, Shield, COND_None, REPNOTIFY_Always);
}

void UGGShieldSet::OnRep_Shield(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UGGShieldSet, Shield, OldValue);

	OnShieldChanged.Broadcast(nullptr, nullptr, nullptr, GetShield() - OldValue.GetCurrentValue(),
	                          OldValue.GetCurrentValue(), GetShield());
}

bool UGGShieldSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	if (!Super::PreGameplayEffectExecute(Data))
	{
		return false;
	}

	ShieldBeforeAttributeChange = GetShield();

	return true;
}

void UGGShieldSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();

	if (Data.EvaluatedData.Attribute == GetShieldDamageAttribute())
	{
		SetShield(FMath::Max(0.0f, GetShield() - GetShieldDamage()));
		SetShieldDamage(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetShieldHealingAttribute())
	{
		SetShield(FMath::Max(0.0f, GetShield() + GetShieldHealing()));
		SetShieldHealing(0.0f);
	}
	else if (Data.EvaluatedData.Attribute == GetShieldAttribute())
	{
		SetShield(FMath::Max(0.0f, GetShield()));
	}

	if (GetShield() != ShieldBeforeAttributeChange)
	{
		OnShieldChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude,
		                          ShieldBeforeAttributeChange, GetShield());
	}
}

void UGGShieldSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	ClampAttribute(Attribute, NewValue);
}

void UGGShieldSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
}

void UGGShieldSet::ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const
{
	if (Attribute == GetShieldAttribute())
	{
		NewValue = FMath::Max(NewValue, 0.0f);
	}
}

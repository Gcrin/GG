// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagnitudeCalculation/GGMMC_SkillCooldownDuration.h"

#include "AbilitySystem/Abilities/GGSkillAbility.h"

float UGGMMC_SkillCooldownDuration::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UGGSkillAbility* SkillAbility = Cast<UGGSkillAbility>(Spec.GetContext().GetAbilityInstance_NotReplicated());

	if (SkillAbility && SkillAbility->GetSkillData())
	{
		return SkillAbility->GetSkillData()->CooldownDuration;
	}

	return 0.0f;
}

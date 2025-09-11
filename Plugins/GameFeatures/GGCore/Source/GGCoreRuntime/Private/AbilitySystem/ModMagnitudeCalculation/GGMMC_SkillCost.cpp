// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/ModMagnitudeCalculation/GGMMC_SkillCost.h"

#include "AbilitySystem/Abilities/GGSkillAbility.h"

float UGGMMC_SkillCost::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const UGGSkillAbility* SkillAbility = Cast<UGGSkillAbility>(Spec.GetContext().GetAbilityInstance_NotReplicated());
	if (!SkillAbility || !SkillAbility->GetSkillData())
	{
		return 0.0f;
	}

	if (!CostTag.IsValid())
	{
		return 0.0f;
	}

	if (const float* CostValue = SkillAbility->GetSkillData()->ResourceCosts.Find(CostTag))
	{
		return -FMath::Abs(*CostValue);
	}

	return 0.0f;
}

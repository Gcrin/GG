// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Executions/GGDamageExecution.h"

#include "AbilitySystem/Attributes/GGDefenseSet.h"
#include "AbilitySystem/Attributes/GGOffenseSet.h"
#include "GGGameplayTags.h"

struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamageAmp);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicDamageAmp);
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicPenetration);

	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalDamageReduction);
	DECLARE_ATTRIBUTE_CAPTUREDEF(MagicDamageReduction);
	DECLARE_ATTRIBUTE_CAPTUREDEF(FlatDamageReduction);

	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGGOffenseSet, CritChance, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGGOffenseSet, CritDamage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGGOffenseSet, PhysicalDamageAmp, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGGOffenseSet, MagicDamageAmp, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGGOffenseSet, PhysicalPenetration, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGGOffenseSet, MagicPenetration, Source, true);

		DEFINE_ATTRIBUTE_CAPTUREDEF(UGGDefenseSet, PhysicalDamageReduction, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGGDefenseSet, MagicDamageReduction, Target, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UGGDefenseSet, FlatDamageReduction, Target, true);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics DmgStatics;
	return DmgStatics;
}

UGGDamageExecution::UGGDamageExecution()
{
	RelevantAttributesToCapture.Add(DamageStatics().CritChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageAmpDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicDamageAmpDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicPenetrationDef);

	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageReductionDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicDamageReductionDef);
	RelevantAttributesToCapture.Add(DamageStatics().FlatDamageReductionDef);
}

void UGGDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
#if WITH_SERVER_CODE
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	float CritChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritChanceDef,
	                                                           FAggregatorEvaluateParameters(), CritChance);
	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CritDamageDef,
	                                                           FAggregatorEvaluateParameters(), CritDamage);
	float PhysicalDamageAmp = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalDamageAmpDef,
	                                                           FAggregatorEvaluateParameters(), PhysicalDamageAmp);
	float MagicDamageAmp = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicDamageAmpDef,
	                                                           FAggregatorEvaluateParameters(), MagicDamageAmp);
	float PhysicalPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalPenetrationDef,
	                                                           FAggregatorEvaluateParameters(), PhysicalPenetration);
	float MagicPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicPenetrationDef,
	                                                           FAggregatorEvaluateParameters(), MagicPenetration);
	float PhysicalDamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().PhysicalDamageReductionDef,
	                                                           FAggregatorEvaluateParameters(), PhysicalDamageReduction);
	float MagicDamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().MagicDamageReductionDef,
	                                                           FAggregatorEvaluateParameters(), MagicDamageReduction);
	float FlatDamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().FlatDamageReductionDef,
	                                                           FAggregatorEvaluateParameters(), FlatDamageReduction);

	const float BasePhysicalDamage = Spec.GetSetByCallerMagnitude(
		GGGameplayTags::Data_Damage_Physical, false, 0.f);
	const float BaseMagicDamage = Spec.GetSetByCallerMagnitude(
		GGGameplayTags::Data_Damage_Magic, false, 0.f);
	const float SkillDamage = Spec.GetSetByCallerMagnitude(
		GGGameplayTags::Ability_SkillDamage, false, 0.f);
	const float SkillDamageMultiplier = Spec.GetSetByCallerMagnitude(
		GGGameplayTags::Ability_SkillDamage_Multiplier, false, 1.0f);


#endif
}

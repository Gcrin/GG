// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Executions/GGDamageExecution.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/Attributes/GGDefenseSet.h"
#include "AbilitySystem/Attributes/GGOffenseSet.h"
#include "AbilitySystem/Attributes/LyraCombatSet.h"
#include "AbilitySystem/Attributes/LyraHealthSet.h"
#include "GGGameplayTags.h"
#include "GameplayEffect.h"
#include "AbilitySystem/Attributes/GGShieldSet.h"

struct FDamageStatics
{
	FGameplayEffectAttributeCaptureDefinition BaseDamageDef;
	FGameplayEffectAttributeCaptureDefinition CritChanceDef;
	FGameplayEffectAttributeCaptureDefinition CritDamageDef;
	FGameplayEffectAttributeCaptureDefinition PhysicalDamageAmpDef;
	FGameplayEffectAttributeCaptureDefinition MagicDamageAmpDef;
	FGameplayEffectAttributeCaptureDefinition PhysicalPenetrationDef;
	FGameplayEffectAttributeCaptureDefinition MagicPenetrationDef;

	FGameplayEffectAttributeCaptureDefinition PhysicalDamageReductionDef;
	FGameplayEffectAttributeCaptureDefinition MagicDamageReductionDef;
	FGameplayEffectAttributeCaptureDefinition FlatDamageReductionDef;
	FGameplayEffectAttributeCaptureDefinition ShieldDef;

	FDamageStatics()
	{
		BaseDamageDef = FGameplayEffectAttributeCaptureDefinition(
			ULyraCombatSet::GetBaseDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
		CritChanceDef = FGameplayEffectAttributeCaptureDefinition(
			UGGOffenseSet::GetCritChanceAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
		CritDamageDef = FGameplayEffectAttributeCaptureDefinition(
			UGGOffenseSet::GetCritDamageAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
		PhysicalDamageAmpDef = FGameplayEffectAttributeCaptureDefinition(
			UGGOffenseSet::GetPhysicalDamageAmpAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
		MagicDamageAmpDef = FGameplayEffectAttributeCaptureDefinition(
			UGGOffenseSet::GetMagicDamageAmpAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
		PhysicalPenetrationDef = FGameplayEffectAttributeCaptureDefinition(
			UGGOffenseSet::GetPhysicalPenetrationAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);
		MagicPenetrationDef = FGameplayEffectAttributeCaptureDefinition(
			UGGOffenseSet::GetMagicPenetrationAttribute(), EGameplayEffectAttributeCaptureSource::Source, true);

		PhysicalDamageReductionDef = FGameplayEffectAttributeCaptureDefinition(
			UGGDefenseSet::GetPhysicalDamageReductionAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
		MagicDamageReductionDef = FGameplayEffectAttributeCaptureDefinition(
			UGGDefenseSet::GetMagicDamageReductionAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
		FlatDamageReductionDef = FGameplayEffectAttributeCaptureDefinition(
			UGGDefenseSet::GetFlatDamageReductionAttribute(), EGameplayEffectAttributeCaptureSource::Target, true);
		ShieldDef = FGameplayEffectAttributeCaptureDefinition(
			UGGShieldSet::GetShieldAttribute(), EGameplayEffectAttributeCaptureSource::Target, false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics DmgStatics;
	return DmgStatics;
}

UGGDamageExecution::UGGDamageExecution()
{
	RelevantAttributesToCapture.Add(DamageStatics().BaseDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageAmpDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicDamageAmpDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicPenetrationDef);

	RelevantAttributesToCapture.Add(DamageStatics().PhysicalDamageReductionDef);
	RelevantAttributesToCapture.Add(DamageStatics().MagicDamageReductionDef);
	RelevantAttributesToCapture.Add(DamageStatics().FlatDamageReductionDef);
	RelevantAttributesToCapture.Add(DamageStatics().ShieldDef);
}

void UGGDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
                                                FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
#if WITH_SERVER_CODE
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	float BaseDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().BaseDamageDef, FAggregatorEvaluateParameters(), BaseDamage);
	float CritChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CritChanceDef, FAggregatorEvaluateParameters(), CritChance);
	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CritDamageDef, FAggregatorEvaluateParameters(), CritDamage);
	float PhysicalDamageAmp = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().PhysicalDamageAmpDef, FAggregatorEvaluateParameters(), PhysicalDamageAmp);
	float MagicDamageAmp = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().MagicDamageAmpDef, FAggregatorEvaluateParameters(), MagicDamageAmp);
	float PhysicalPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().PhysicalPenetrationDef, FAggregatorEvaluateParameters(), PhysicalPenetration);
	float MagicPenetration = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().MagicPenetrationDef, FAggregatorEvaluateParameters(), MagicPenetration);
	float PhysicalDamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().PhysicalDamageReductionDef, FAggregatorEvaluateParameters(), PhysicalDamageReduction);
	float MagicDamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().MagicDamageReductionDef, FAggregatorEvaluateParameters(), MagicDamageReduction);
	float FlatDamageReduction = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().FlatDamageReductionDef, FAggregatorEvaluateParameters(), FlatDamageReduction);
	float TargetShield = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().ShieldDef, FAggregatorEvaluateParameters(), TargetShield);

	const float SkillDamage = Spec.GetSetByCallerMagnitude(
		GGGameplayTags::SetByCaller_SkillDamage, false, 0.f);
	const float SkillDamageMultiplier = Spec.GetSetByCallerMagnitude(
		GGGameplayTags::SetByCaller_SkillDamage_Multiplier, false, 1.f);

	float RealBaseDamage = 0.f;
	float DamageAmp = 0.f;
	float DamageReduction = 0.f;
	float Penetration = 0.f;
	FGameplayTag EventTag;

	if (Spec.Def->GetGrantedTags().HasTag(GGGameplayTags::Damage_Type_Physical))
	{
		RealBaseDamage = BaseDamage;
		DamageAmp = PhysicalDamageAmp;
		DamageReduction = PhysicalDamageReduction;
		Penetration = PhysicalPenetration;
		EventTag = GGGameplayTags::Event_Combat_DamageDealt_Physical;
	}
	else if (Spec.Def->GetGrantedTags().HasTag(GGGameplayTags::Damage_Type_Magic))
	{
		RealBaseDamage = 0.f;
		DamageAmp = MagicDamageAmp;
		DamageReduction = MagicDamageReduction;
		Penetration = MagicPenetration;
		EventTag = GGGameplayTags::Event_Combat_DamageDealt_Magic;
	}
	else
	{
		const FString EffectName = Spec.Def ? Spec.Def->GetName() : TEXT("Unknown Effect");
		ensureMsgf(
			false,
			TEXT(
				"GGDamageExecution: GameplayEffect '%s' lacks a required Damage Type Tag (e.g., Damage.Type.Physical)."
			), *EffectName);

		return;
	}

	// 계산
	float FinalDamage = 0.f;
	float ApplyCritMultiplier = 1.f;
	const float RandValue = FMath::FRand();
	if (RandValue < CritChance)
	{
		ApplyCritMultiplier = CritDamage;
	}

	if (DamageReduction < 0.f)
	{
		Penetration = 0.f;
	}

	// 데미지 = (((기본데미지 + 스킬데미지) * 스킬배율 * 치피배율) * (1 + 뎀증율) * (1-피감율)) - 고정피해감소수치
	FinalDamage = (((RealBaseDamage + SkillDamage) * SkillDamageMultiplier * ApplyCritMultiplier)
		* (1.f + DamageAmp) * (1.f - (DamageReduction * (1.f - Penetration)))) - FlatDamageReduction;

	FinalDamage = FMath::Max(0.f, FinalDamage);

	float DamageToHealth = FinalDamage;

	if (TargetShield > 0.f)
	{
		const float DamageToShield = FMath::Min(DamageToHealth, TargetShield);
		DamageToHealth -= DamageToShield;

		// 보호막에 가해질 데미지 적용
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			UGGShieldSet::GetShieldDamageAttribute(), EGameplayModOp::Additive, DamageToShield));
	}

	// 체력에 가해질 데미지 적용
	if (DamageToHealth > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
			ULyraHealthSet::GetDamageAttribute(), EGameplayModOp::Additive, DamageToHealth));

		UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
		AActor* SourceActor = SourceASC ? SourceASC->GetAvatarActor() : nullptr;

		if (SourceActor && EventTag.IsValid())
		{
			FGameplayEventData EventData;
			EventData.EventTag = EventTag;
			EventData.EventMagnitude = DamageToHealth;
			EventData.Instigator = SourceActor;
			EventData.Target = ExecutionParams.GetTargetAbilitySystemComponent()->GetAvatarActor();
			EventData.ContextHandle = ExecutionParams.GetOwningSpec().GetEffectContext();

			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(SourceActor, EventData.EventTag, EventData);
		}
	}

#endif
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "GGUtilitySet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GGCORERUNTIME_API UGGUtilitySet : public ULyraAttributeSet
{
	GENERATED_BODY()

public:

	UGGUtilitySet();

	ATTRIBUTE_ACCESSORS(UGGUtilitySet, StaminaRegen);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, StaminaRegenPercent);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, ManaRegen);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, ManaRegenPercent);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, HealthRegen);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, HealthRegenPercent);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, MoveSpeed);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, CooldownReduction);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, PhysicalDamageAbsorption);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, MagicDamageAbsorption);

	mutable FLyraAttributeEvent OnStaminaRegenChanged;
	mutable FLyraAttributeEvent OnStaminaRegenPercentChanged;
	mutable FLyraAttributeEvent OnManaRegenChanged;
	mutable FLyraAttributeEvent OnManaRegenPercentChanged;
	mutable FLyraAttributeEvent OnHealthRegenChanged;
	mutable FLyraAttributeEvent OnHealthRegenPercentChanged;
	mutable FLyraAttributeEvent OnMoveSpeedChanged;
	mutable FLyraAttributeEvent OnCooldownReductionChanged;
	mutable FLyraAttributeEvent OnPhysicalDamageAbsorptionChanged;
	mutable FLyraAttributeEvent OnMagicDamageAbsorptionChanged;

protected:

	UFUNCTION()
	virtual void OnRep_StaminaRegen(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_StaminaRegenPercent(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_ManaRegen(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_ManaRegenPercent(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_HealthRegen(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_HealthRegenPercent(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MoveSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_CooldownReduction(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_PhysicalDamageAbsorption(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicDamageAbsorption(const FGameplayAttributeData& OldValue);

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:

	// n초당 기력 회복 (수치)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegen, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaRegen;

	// n초당 기력 회복 (%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegenPercent, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaRegenPercent;

	// n초당 마력 회복 (수치)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegen, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ManaRegen;

	// n초당 마력 회복 (%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegenPercent, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ManaRegenPercent;

	// n초당 체력 회복 (수치)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegen, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HealthRegen;

	// n초당 체력 회복 (%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegenPercent, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HealthRegenPercent;

	// 이동 속도 (수치, 최소 0.0f)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MoveSpeed, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MoveSpeed;

	// 스킬 쿨타임 감소 (예: 0.1 = 10% 감소)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CooldownReduction, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CooldownReduction;

	// 물리 피해 흡수 (준 물리 피해의 일부를 체력으로 전환, 예: 0.05 = 5% 흡수)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamageAbsorption, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData PhysicalDamageAbsorption;

	// 마법 피해 흡수 (준 마법 피해의 일부를 체력으로 전환, 예: 0.05 = 5% 흡수)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDamageAbsorption, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MagicDamageAbsorption;
};

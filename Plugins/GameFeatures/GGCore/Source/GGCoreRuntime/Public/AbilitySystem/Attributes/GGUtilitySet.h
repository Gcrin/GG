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

	ATTRIBUTE_ACCESSORS(UGGUtilitySet, StaminaRegenRate);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, ManaRegenRate);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, HealthRegenRate);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, MoveSpeed);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, CooldownReduction);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, PhysicalDamageAbsorption);
	ATTRIBUTE_ACCESSORS(UGGUtilitySet, MagicDamageAbsorption);

	mutable FLyraAttributeEvent OnStaminaRegenRateChanged;
	mutable FLyraAttributeEvent OnManaRegenRateChanged;
	mutable FLyraAttributeEvent OnHealthRegenRateChanged;
	mutable FLyraAttributeEvent OnMoveSpeedChanged;
	mutable FLyraAttributeEvent OnCooldownReductionChanged;
	mutable FLyraAttributeEvent OnPhysicalDamageAbsorptionChanged;
	mutable FLyraAttributeEvent OnMagicDamageAbsorptionChanged;

protected:

	UFUNCTION()
	virtual void OnRep_StaminaRegenRate(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_ManaRegenRate(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_HealthRegenRate(const FGameplayAttributeData& OldValue);

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

	// 초당 기력 회복 속도
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegenRate, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaRegenRate;

	// 초당 마력 회복 속도
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegenRate, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ManaRegenRate;

	// 초당 체력 회복 속도
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegenRate, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData HealthRegenRate;

	// 이동 속도
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MoveSpeed, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MoveSpeed;

	// 스킬 쿨타임 감소 (예: 10.0 = 10% 감소)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CooldownReduction, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CooldownReduction;

	// 물리 피해 흡수 (준 물리 피해의 일부를 체력으로 전환, 예: 5.0 = 5% 흡수)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamageAbsorption, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData PhysicalDamageAbsorption;

	// 마법 피해 흡수 (준 마법 피해의 일부를 체력으로 전환, 예: 5.0 = 5% 흡수)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDamageAbsorption, Category = "GG|Utility", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MagicDamageAbsorption;
};

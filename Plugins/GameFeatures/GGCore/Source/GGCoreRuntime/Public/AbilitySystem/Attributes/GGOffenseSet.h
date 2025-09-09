// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "GGOffenseSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GGCORERUNTIME_API UGGOffenseSet : public ULyraAttributeSet
{
	GENERATED_BODY()

public:

	UGGOffenseSet();
	
	ATTRIBUTE_ACCESSORS(UGGOffenseSet, CritChance);
	ATTRIBUTE_ACCESSORS(UGGOffenseSet, CritDamage);
	ATTRIBUTE_ACCESSORS(UGGOffenseSet, PhysicalDamageAmp);
	ATTRIBUTE_ACCESSORS(UGGOffenseSet, MagicDamageAmp);
	ATTRIBUTE_ACCESSORS(UGGOffenseSet, AttackSpeed);
	ATTRIBUTE_ACCESSORS(UGGOffenseSet, PhysicalPenetration);
	ATTRIBUTE_ACCESSORS(UGGOffenseSet, MagicPenetration);
	ATTRIBUTE_ACCESSORS(UGGOffenseSet, CastSpeed);

	mutable FLyraAttributeEvent OnCritChanceChanged;
	mutable FLyraAttributeEvent OnCritDamageChanged;
	mutable FLyraAttributeEvent OnPhysicalDamageAmpChanged;
	mutable FLyraAttributeEvent OnMagicDamageAmpChanged;
	mutable FLyraAttributeEvent OnAttackSpeedChanged;
	mutable FLyraAttributeEvent OnPhysicalPenetrationChanged;
	mutable FLyraAttributeEvent OnMagicPenetrationChanged;
	mutable FLyraAttributeEvent OnCastSpeedChanged;

protected:

	UFUNCTION()
	virtual void OnRep_CritChance(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_CritDamage(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_PhysicalDamageAmp(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicDamageAmp(const FGameplayAttributeData& OldValue);
	
	UFUNCTION()
	virtual void OnRep_AttackSpeed(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_PhysicalPenetration(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicPenetration(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_CastSpeed(const FGameplayAttributeData& OldValue);

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:

	// 치명타 확률 (예: 0.05 = 5%, 0% ~ 100%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritChance, Category = "GG|Offense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CritChance;

	// 치명타 피해량 (예: 2.0 = 200%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CritDamage, Category = "GG|Offense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CritDamage;

	// 물리 피해 증폭 (예: 0.1 = 10%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamageAmp, Category = "GG|Offense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData PhysicalDamageAmp;

	// 마법 피해 증폭 (예: 0.1 = 10%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDamageAmp, Category = "GG|Offense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MagicDamageAmp;

	// 공격 속도 (예: 0.2 = 20%, 1.2 = 120%, 최소 20% ~)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_AttackSpeed, Category = "GG|Offense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData AttackSpeed;

	// 물리 관통력 (0% ~ 100%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalPenetration, Category = "GG|Offense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData PhysicalPenetration;

	// 마법 관통력 (0% ~ 100%)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicPenetration, Category = "GG|Offense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MagicPenetration;

	// 시전 속도 (예: 0.2 = 20%, 1.2 = 120%, 최소 20% ~)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CastSpeed, Category = "GG|Offense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData CastSpeed;
};

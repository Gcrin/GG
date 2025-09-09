// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "GGDefenseSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GGCORERUNTIME_API UGGDefenseSet : public ULyraAttributeSet
{
	GENERATED_BODY()

public:

	UGGDefenseSet();
	
	ATTRIBUTE_ACCESSORS(UGGDefenseSet, PhysicalDamageReduction);
	ATTRIBUTE_ACCESSORS(UGGDefenseSet, MagicDamageReduction);
	ATTRIBUTE_ACCESSORS(UGGDefenseSet, FlatDamageReduction);

	mutable FLyraAttributeEvent OnPhysicalDamageReductionChanged;
	mutable FLyraAttributeEvent OnMagicDamageReductionChanged;
	mutable FLyraAttributeEvent OnFlatDamageReductionChanged;

protected:

	UFUNCTION()
	virtual void OnRep_PhysicalDamageReduction(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicDamageReduction(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_FlatDamageReduction(const FGameplayAttributeData& OldValue);

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

private:

	// 물리 피해 감소 (예: 0.1 = 10% 감소)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamageReduction, Category = "GG|Defense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData PhysicalDamageReduction;

	// 마법 피해 감소 (예: 0.1 = 10% 감소)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDamageReduction, Category = "GG|Defense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MagicDamageReduction;

	// 고정 피해 감소 (수치)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDamageReduction, Category = "GG|Defense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData FlatDamageReduction;
};

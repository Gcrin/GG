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
	ATTRIBUTE_ACCESSORS(UGGDefenseSet, PhysicalDamageAbsorption);
	ATTRIBUTE_ACCESSORS(UGGDefenseSet, MagicDamageAbsorption);

	mutable FLyraAttributeEvent OnPhysicalDamageReductionChanged;
	mutable FLyraAttributeEvent OnMagicDamageReductionChanged;
	mutable FLyraAttributeEvent OnPhysicalDamageAbsorptionChanged;
	mutable FLyraAttributeEvent OnMagicDamageAbsorptionChanged;

protected:

	UFUNCTION()
	virtual void OnRep_PhysicalDamageReduction(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicDamageReduction(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_PhysicalDamageAbsorption(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MagicDamageAbsorption(const FGameplayAttributeData& OldValue);

private:

	// 물리 피해 감소 (예: 10.0 = 10% 감소)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamageReduction, Category = "GG|Defense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData PhysicalDamageReduction;

	// 마법 피해 감소 (예: 10.0 = 10% 감소)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDamageReduction, Category = "GG|Defense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MagicDamageReduction;

	// 물리 피해 흡수 (받은 물리 피해의 일부를 체력으로 전환, 예: 5.0 = 5% 흡수)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalDamageAbsorption, Category = "GG|Defense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData PhysicalDamageAbsorption;

	// 마법 피해 흡수 (받은 마법 피해의 일부를 체력으로 전환, 예: 5.0 = 5% 흡수)
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MagicDamageAbsorption, Category = "GG|Defense", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MagicDamageAbsorption;
};

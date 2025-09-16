// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"
#include "GGShieldSet.generated.h"

/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API UGGShieldSet : public ULyraAttributeSet
{
	GENERATED_BODY()

public:
	
	UGGShieldSet();

	ATTRIBUTE_ACCESSORS(UGGShieldSet, Shield);
	ATTRIBUTE_ACCESSORS(UGGShieldSet, MaxShield);
	ATTRIBUTE_ACCESSORS(UGGShieldSet, ShieldDamage);
	
	mutable FLyraAttributeEvent OnShieldChanged;
	mutable FLyraAttributeEvent OnMaxShieldChanged;

protected:

	UFUNCTION()
	virtual void OnRep_Shield(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	virtual void OnRep_MaxShield(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;

public:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Shield, Category = "GG|Shield", Meta = (DisplayName = "보호막", AllowPrivateAccess = true))
	FGameplayAttributeData Shield;
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxShield, Category = "GG|Shield", Meta = (DisplayName = "보호막", AllowPrivateAccess = true))
	FGameplayAttributeData MaxShield;
	
	float ShieldBeforeAttributeChange;
	float MaxShieldBeforeAttributeChange;

	UPROPERTY(BlueprintReadOnly, Category = "GG|Shield", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ShieldDamage;
	
};

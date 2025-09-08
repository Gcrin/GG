// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "AbilitySystem/Attributes/LyraAttributeSet.h"

#include "GGResourceSet.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class GGCORERUNTIME_API UGGResourceSet : public ULyraAttributeSet
{
	GENERATED_BODY()

public:

	UGGResourceSet();

	ATTRIBUTE_ACCESSORS(UGGResourceSet, Mana);
	ATTRIBUTE_ACCESSORS(UGGResourceSet, MaxMana);
	ATTRIBUTE_ACCESSORS(UGGResourceSet, Stamina);
	ATTRIBUTE_ACCESSORS(UGGResourceSet, MaxStamina);
	ATTRIBUTE_ACCESSORS(UGGResourceSet, ManaCost);
	ATTRIBUTE_ACCESSORS(UGGResourceSet, ManaGain);
	ATTRIBUTE_ACCESSORS(UGGResourceSet, StaminaCost);
	ATTRIBUTE_ACCESSORS(UGGResourceSet, StaminaGain);

	mutable FLyraAttributeEvent OnManaChanged;
	mutable FLyraAttributeEvent OnMaxManaChanged;
	
	mutable FLyraAttributeEvent OnStaminaChanged;
	mutable FLyraAttributeEvent OnMaxStaminaChanged;
	
	mutable FLyraAttributeEvent OnOutOfMana;
	mutable FLyraAttributeEvent OnOutOfStamina;

protected:

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldValue);

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldValue);

	virtual bool PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void PreAttributeBaseChange(const FGameplayAttribute& Attribute, float& NewValue) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void ClampAttribute(const FGameplayAttribute& Attribute, float& NewValue) const;
	
private:

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "GG|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "GG|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxMana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "GG|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData Stamina;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "GG|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData MaxStamina;

	bool bOutOfMana;
	bool bOutOfStamina;

	float MaxManaBeforeAttributeChange;
	float ManaBeforeAttributeChange;
	float MaxStaminaBeforeAttributeChange;
	float StaminaBeforeAttributeChange;

	UPROPERTY(BlueprintReadOnly, Category = "GG|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ManaCost;

	UPROPERTY(BlueprintReadOnly, Category = "GG|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData ManaGain;

	UPROPERTY(BlueprintReadOnly, Category = "GG|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaCost;

	UPROPERTY(BlueprintReadOnly, Category = "GG|Resource", Meta = (AllowPrivateAccess = true))
	FGameplayAttributeData StaminaGain;

};

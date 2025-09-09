// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GGResourceComponent.h"

#include "LyraLogChannels.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AbilitySystem/Attributes/GGResourceSet.h"

UGGResourceComponent::UGGResourceComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	AbilitySystemComponent = nullptr;
	ResourceSet = nullptr;
}

void UGGResourceComponent::InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC)
{
	AActor* Owner = GetOwner();
	check(Owner);

	if (AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("GGResourceComponent: Resource component for owner [%s] has already been initialized with an ability system."), *GetNameSafe(Owner));
		return;
	}

	AbilitySystemComponent = InASC;
	if (!AbilitySystemComponent)
	{
		UE_LOG(LogLyra, Error, TEXT("GGResourceComponent: Cannot initialize Resource component for owner [%s] with NULL ability system."), *GetNameSafe(Owner));
		return;
	}

	ResourceSet = AbilitySystemComponent->GetSet<UGGResourceSet>();
	if (!ResourceSet)
	{
		UE_LOG(LogLyra, Error, TEXT("GGResourceComponent: Cannot initialize Resource component for owner [%s] with NULL health set on the ability system."), *GetNameSafe(Owner));
		return;
	}

	ResourceSet->OnManaChanged.AddUObject(this, &ThisClass::HandleManaChanged);
	ResourceSet->OnMaxManaChanged.AddUObject(this, &ThisClass::HandleMaxManaChanged);
	ResourceSet->OnStaminaChanged.AddUObject(this, &ThisClass::HandleStaminaChanged);
	ResourceSet->OnMaxStaminaChanged.AddUObject(this, &ThisClass::HandleMaxStaminaChanged);
	
	AbilitySystemComponent->SetNumericAttributeBase(UGGResourceSet::GetManaAttribute(), ResourceSet->GetMaxMana());
	AbilitySystemComponent->SetNumericAttributeBase(UGGResourceSet::GetStaminaAttribute(), ResourceSet->GetMaxStamina());

	ClearGameplayTags();

	OnManaChanged.Broadcast(this, ResourceSet->GetMana(), ResourceSet->GetMana(), nullptr);
	OnMaxManaChanged.Broadcast(this, ResourceSet->GetMaxMana(), ResourceSet->GetMaxMana(), nullptr);
	OnStaminaChanged.Broadcast(this, ResourceSet->GetStamina(), ResourceSet->GetStamina(), nullptr);
	OnMaxStaminaChanged.Broadcast(this, ResourceSet->GetMaxStamina(), ResourceSet->GetMaxStamina(), nullptr);
}

void UGGResourceComponent::UninitializeFromAbilitySystem()
{
	ClearGameplayTags();
	
	if (ResourceSet)
	{
		ResourceSet->OnManaChanged.RemoveAll(this);
		ResourceSet->OnMaxManaChanged.RemoveAll(this);
	}

	ResourceSet = nullptr;
	AbilitySystemComponent = nullptr;
}

float UGGResourceComponent::GetMana() const
{
	return (ResourceSet ? ResourceSet->GetMana() : 0.0f);
}

float UGGResourceComponent::GetMaxMana() const
{
	return (ResourceSet ? ResourceSet->GetMaxMana() : 0.0f);
}

float UGGResourceComponent::GetStamina() const
{
	return (ResourceSet ? ResourceSet->GetStamina() : 0.0f);
}

float UGGResourceComponent::GetMaxStamina() const
{
	return(ResourceSet ? ResourceSet->GetMaxStamina() : 0.0f);
}

float UGGResourceComponent::GetManaNormalized() const
{
	if (ResourceSet)
	{
		const float Mana = ResourceSet->GetMana();
		const float MaxMana = ResourceSet->GetMaxMana();

		return ((MaxMana > 0.0f) ? (Mana / MaxMana) : 0.0f);
	}

	return 0.0f;
}

float UGGResourceComponent::GetStaminaNormalized() const
{
	if (ResourceSet)
	{
		const float Stamina = ResourceSet->GetStamina();
		const float MaxStamina = ResourceSet->GetMaxStamina();

		return ((MaxStamina > 0.0f) ? (Stamina / MaxStamina) : 0.0f);
	}

	return 0.0f;
}

void UGGResourceComponent::OnUnregister()
{
	UninitializeFromAbilitySystem();
	
	Super::OnUnregister();
}

void UGGResourceComponent::ClearGameplayTags()
{
}

void UGGResourceComponent::HandleManaChanged(AActor* Instigator, AActor* Causer, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	OnManaChanged.Broadcast(this, OldValue, NewValue, Instigator);
}

void UGGResourceComponent::HandleMaxManaChanged(AActor* Instigator, AActor* Causer, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	OnMaxManaChanged.Broadcast(this, OldValue, NewValue, Instigator);
}
	
void UGGResourceComponent::HandleStaminaChanged(AActor* Instigator, AActor* Causer, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	OnStaminaChanged.Broadcast(this, OldValue, NewValue, Instigator);
}

void UGGResourceComponent::HandleMaxStaminaChanged(AActor* Instigator, AActor* Causer, const FGameplayEffectSpec* EffectSpec, float EffectMagnitude, float OldValue, float NewValue)
{
	OnMaxStaminaChanged.Broadcast(this, OldValue, NewValue, Instigator);
}

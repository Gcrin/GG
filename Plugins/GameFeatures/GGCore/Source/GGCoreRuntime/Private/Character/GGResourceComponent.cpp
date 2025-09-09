// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GGResourceComponent.h"


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
	
}

void UGGResourceComponent::UninitializeFromAbilitySystem()
{
	
}

void UGGResourceComponent::ClearGameplayTags()
{
}

float UGGResourceComponent::GetMana() const
{
	return 0.0f;
}

float UGGResourceComponent::GetMaxMana() const
{
	return 0.0f;
}

float UGGResourceComponent::GetStamina() const
{
	return 0.0f;
}

float UGGResourceComponent::GetMaxStamina() const
{
	return 0.0f;
}

float UGGResourceComponent::GetManaNormalized() const
{
	return 0.0f;
}

float UGGResourceComponent::GetStaminaNormalized() const
{
	return 0.0f;
}

void UGGResourceComponent::OnUnregister()
{
	
}

void UGGResourceComponent::HandleManaChanged(FOnAttributeChangeData& ChangeData)
{
	
}

void UGGResourceComponent::HandleStaminaChanged(FOnAttributeChangeData& ChangeData)
{
	
}

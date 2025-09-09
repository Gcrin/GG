// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/GameFrameworkComponent.h"

#include "GGResourceComponent.generated.h"


struct FOnAttributeChangeData;
class UGGResourceSet;
class ULyraAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGGResource_AttributeChanged, UGGResourceComponent*, ResourceComponent, float, OldValue, float, NewValue, AActor*, Instigator);

/**
 * 
 */
UCLASS(Blueprintable, Meta=(BlueprintSpawnableComponent))
class GGCORERUNTIME_API UGGResourceComponent : public UGameFrameworkComponent
{
	GENERATED_BODY()

public:

	UGGResourceComponent(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintPure, Category = "GG|Resource")
	static UGGResourceComponent* GetResourceComponent(const AActor* Actor) { return (Actor ? Actor->FindComponentByClass<UGGResourceComponent>() : nullptr); }

	UFUNCTION(BlueprintCallable, Category = "GG|Resource")
	void InitializeWithAbilitySystem(ULyraAbilitySystemComponent* InASC);

	UFUNCTION(BlueprintCallable, Category = "GG|Resource")
	void UninitializeFromAbilitySystem();

	UFUNCTION(BlueprintCallable, Category = "GG|Resource")
	float GetMana() const;

	UFUNCTION(BlueprintCallable, Category = "GG|Resource")
	float GetMaxMana() const;

	UFUNCTION(BlueprintCallable, Category = "GG|Resource")
	float GetStamina() const;

	UFUNCTION(BlueprintCallable, Category = "GG|Resource")
	float GetMaxStamina() const;

	UFUNCTION(BlueprintCallable, Category = "GG|Resource")
	float GetManaNormalized() const;

	UFUNCTION(BlueprintCallable, Category = "GG|Resource")
	float GetStaminaNormalized() const;

public:

	UPROPERTY(BlueprintAssignable)
	FGGResource_AttributeChanged OnManaChanged;

	UPROPERTY(BlueprintAssignable)
	FGGResource_AttributeChanged OnMaxManaChanged;

	UPROPERTY(BlueprintAssignable)
	FGGResource_AttributeChanged OnStaminaChanged;

	UPROPERTY(BlueprintAssignable)
	FGGResource_AttributeChanged OnMaxStaminaChanged;

protected:

	virtual void OnUnregister() override;

	void ClearGameplayTags();

	virtual void HandleManaChanged(FOnAttributeChangeData& ChangeData);
	virtual void HandleStaminaChanged(FOnAttributeChangeData& ChangeData);

protected:

	UPROPERTY()
	TObjectPtr<ULyraAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<const UGGResourceSet> ResourceSet;
};

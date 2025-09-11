// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayEffectExecutionCalculation.h"
#include "GGDamageExecution.generated.h"

/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API UGGDamageExecution : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()

public:

	UGGDamageExecution();

protected:

	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/LyraPlayerState.h"
#include "GGPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API AGGPlayerState : public ALyraPlayerState
{
	GENERATED_BODY()

public:

	AGGPlayerState(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

private:

	UPROPERTY()
	TObjectPtr<const class UGGResourceSet> ResourceSet;

	UPROPERTY()
	TObjectPtr<const class UGGOffenseSet> OffenseSet;

	UPROPERTY()
	TObjectPtr<const class UGGDefenseSet> DefenseSet;

	UPROPERTY()
	TObjectPtr<const class UGGUtilitySet> UtilitySet;

	UPROPERTY()
	TObjectPtr<const class UGGShieldSet> ShieldSet;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/Abilities/GGSkillAbility.h"
#include "GGAbilityUIUpdateMessage.generated.h"
/**
 * 
 */
USTRUCT(BlueprintType)
struct FGGAbilityUIUpdateMessage
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<AActor> Owner = nullptr;

	UPROPERTY(BlueprintReadWrite)
	TObjectPtr<UGGSkillAbility> SkillAbility;

	UPROPERTY(BlueprintReadWrite)
	FGameplayTag InputTag;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "GGMMC_SkillCost.generated.h"

/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API UGGMMC_SkillCost : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:
	/**
	 * Cost GE 블루프린트의 모디파이어에서 직접 설정할 비용 태그입니다.
	 * 이 태그를 기준으로 SkillData에서 실제 비용 값을 조회합니다.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GG||Cost", Meta = (Categories = "SetByCaller.Resource"))
	FGameplayTag CostTag;

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
};

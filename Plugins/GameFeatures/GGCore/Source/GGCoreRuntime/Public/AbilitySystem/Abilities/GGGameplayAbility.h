// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/LyraGameplayAbility.h"
#include "AbilitySystem/Data/GGSkillDataBase.h"
#include "AbilitySystem/Data/GGSkillType.h"
#include "GGGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API UGGGameplayAbility : public ULyraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "GG|Skill")
	UGGSkillDataBase* GetSkillData() const { return SkillData; }

protected:
	/**
	 * @brief SkillData에 정의된 게임플레이 이펙트 중, 주어진 조건에 맞는 효과들을 대상에게 적용합니다.
	 * @param Condition 필터링할 적용 조건입니다.
	 * @param Target 효과를 적용할 대상 액터입니다. nullptr이거나 지정되지 않은 경우, 어빌리티 시전자 자신에게 효과를 적용합니다.
	 */
	UFUNCTION(BlueprintCallable, Category = "GG|Skill|Effects", meta = (DisplayName = "Apply Effects by Condition"))
	void ApplyEffectsByCondition(ESkillEffectApplyCondition Condition, AActor* Target = nullptr);
	/**
	 * @brief 스킬 데이터에서 주어진 조건에 맞는 모든 GameplayEffectSpec을 생성하여 반환합니다.
	 *        이 함수는 효과 적용에 필요한 모든 컨텍스트 정보를 Spec에 담습니다.
	 * @param Condition 필터링할 생명주기 조건입니다.
	 * @return 생성된 GameplayEffectSpecHandle의 배열입니다.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "GG|Skill|Effects", meta = (DisplayName = "Create Effect Specs by Condition"))
    TArray<FGameplayEffectSpecHandle> CreateEffectSpecsByCondition(ESkillEffectApplyCondition Condition);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GG|Skill")
	TObjectPtr<UGGSkillDataBase> SkillData;
};

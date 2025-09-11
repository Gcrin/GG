// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameplayTagContainer.h"
#include "GGSkillType.h"
#include "Engine/DataAsset.h"
#include "GGSkillDataBase.generated.h"

/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API UGGSkillDataBase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	// === 기본 정보 ===

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Basic", meta=(DisplayName="스킬 식별 태그"))
	FGameplayTag SkillIdentityTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Basic", meta=(DisplayName="스킬 이름"))
	FText SkillName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Basic", meta=(DisplayName="스킬 설명"))
	FText SkillDescription;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Basic", meta=(DisplayName="스킬 아이콘"))
	TObjectPtr<UTexture2D> SkillIcon;

	// === 리소스 ===

	/**
	 * 이 스킬의 비용을 정의하는 GameplayEffect 클래스입니다.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GG|Resource", meta=(DisplayName="비용 게임플레이 이펙트"))
	TSubclassOf<UGameplayEffect> CostGameplayEffect;

	/**
	 * CostGameplayEffect에 주입할 태그와 비용 수치입니다.
	 * 이 값은 SetByCaller를 통해 GE의 Magnitude로 설정됩니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Resource",
		meta=(DisplayName="리소스 비용", Categories = "SetByCaller.Resource", ForceInlineRow))
	TMap<FGameplayTag, float> ResourceCosts;

	/**
	 * 이 스킬의 쿨다운을 정의하는 GameplayEffect 클래스입니다.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GG|Resource", meta=(DisplayName="재사용 대기시간 게임플레이 이펙트"))
	TSubclassOf<UGameplayEffect> CooldownGameplayEffect;

	/**
	 * 이 스킬의 고유 쿨다운을 식별하는 태그입니다. 
	 * 이 태그가 캐릭터에게 적용되어 있는 동안 이 스킬은 재사용할 수 없습니다.
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GG|Resource", meta=(DisplayName="재사용 대기시간 태그"))
	FGameplayTagContainer CooldownTags;

	/**
	 * CooldownGameplayEffect에 주입할 실제 쿨다운 시간(초)입니다.
	 * 이 값은 SetByCaller를 통해 GE의 지속시간으로 설정됩니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Resource", meta=(DisplayName="재사용 대기시간"))
	float CooldownDuration = 1.0f;


	// === 시전 ===

	/**
	 * @brief 스킬 발동 전까지 필요한 시전 시간(채널링)입니다. (단위: 초)
	 * 0보다 크면, 해당 시간 동안 채널링 후에 스킬의 핵심 로직(OnHitEffects 등)이 발동됩니다.
	 * 0이면 즉시 발동 로직으로 넘어갑니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Casting", meta = (DisplayName="시전 시간", ClampMin = "0.0"))
	float CastTime = 0.0f;

	/**
	 * @brief 스킬의 위력을 모으는 데 필요한 최대 차지 시간입니다. (단위: 초)
	 * 0보다 크면, 스킬이 차지 스킬로 동작합니다.
	 * 0이면 차지 기능이 없는 스킬입니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Casting", meta = (DisplayName="차지 시간", ClampMin = "0.0"))
	float ChargeTime = 0.0f;

	// === GameplayEffect 적용 ===

	/**
	 * 이 스킬과 관련된 모든 GameplayEffect 목록입니다.
	 * 각 효과는 지정된 조건이 충족될 때 적용됩니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Effects", meta=(DisplayName="게임플레이 이펙트 목록"))
	TArray<FSkillEffectData> GameplayEffects;

	// === 스킬용 확장 데이터 ===

	// 스킬에서 사용할 커스텀 float 파라미터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Custom Parameters", meta = (ForceInlineRow))
	TMap<FGameplayTag, float> FloatParameters;

	// 스킬에서 사용할 커스텀 int32 파라미터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Custom Parameters", meta = (ForceInlineRow))
	TMap<FGameplayTag, int32> IntParameters;

	// 스킬에서 사용할 커스텀 bool 파라미터
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GG|Custom Parameters", meta = (ForceInlineRow))
	TMap<FGameplayTag, bool> BoolParameters;

	UFUNCTION(BlueprintPure, Category = "GG|Skill Data")
	float GetFloatParameter(FGameplayTag Key, float DefaultValue = 0.0f) const
	{
		if (const float* Value = FloatParameters.Find(Key))
		{
			return *Value;
		}

#if !UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Log,
		       TEXT("GetFloatParameter: 키 '%s' 를 DataAsset '%s' 에서 찾을 수 없습니다. 기본값 %f 을 반환합니다."),
		       *Key.ToString(), *GetName(), DefaultValue);
#endif

		return DefaultValue;
	}

	UFUNCTION(BlueprintPure, Category = "GG|Skill Data")
	int32 GetIntParameter(FGameplayTag Key, int32 DefaultValue = 0) const
	{
		if (const int32* Value = IntParameters.Find(Key))
		{
			return *Value;
		}

#if !UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Log,
		       TEXT("GetIntParameter: 키 '%s' 를 DataAsset '%s' 에서 찾을 수 없습니다. 기본값 %d 을 반환합니다."),
		       *Key.ToString(), *GetName(), DefaultValue);
#endif

		return DefaultValue;
	}

	UFUNCTION(BlueprintPure, Category = "GG|Skill Data")
	bool GetBoolParameter(FGameplayTag Key, bool DefaultValue = false) const
	{
		if (const bool* Value = BoolParameters.Find(Key))
		{
			return *Value;
		}

#if !UE_BUILD_SHIPPING
		UE_LOG(LogTemp, Log,
		       TEXT("GetBoolParameter: 키 '%s' 를 DataAsset '%s' 에서 찾을 수 없습니다. 기본값 %s 을 반환합니다."),
		       *Key.ToString(), *GetName(), DefaultValue ? TEXT("true") : TEXT("false"));
#endif

		return DefaultValue;
	}
};

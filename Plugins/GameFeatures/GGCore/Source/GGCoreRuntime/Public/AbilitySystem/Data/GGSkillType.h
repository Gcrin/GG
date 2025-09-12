// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GGSkillType.generated.h"

/**
 * @struct FSkillEffectData
 * @brief GameplayEffect와 그 적용 조건을 함께 캡슐화하는 데이터 구조체입니다.
 * 
 * 이 구조체는 "어떤 조건에서, 어떤 값을 가진, 어떤 효과를 적용할 것인가?"에 대한 정보를 담고 있습니다.
 */
USTRUCT(BlueprintType)
struct FSkillEffectData
{
	GENERATED_BODY()

	/**
	 * @brief 적용할 GameplayEffect의 클래스입니다.
	 * 
	 * 데미지, 치유, 버프, 디버프 등 실제 게임플레이 변화를 일으키는 핵심 애셋입니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffect", meta=(DisplayName="이펙트 클래스"))
	TSubclassOf<class UGameplayEffect> EffectClass;

	/**
	 * @brief EffectClass에 SetByCaller 방식으로 전달할 데이터 맵입니다.
	 * 
	 * 태그를 키로 사용하여 동적인 수치(데미지, 치유량, 지속시간 등)를 GameplayEffect에 주입할 수 있습니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GameplayEffect", meta = (ForceInlineRow,
		DisplayName="SetByCaller 수치 (SetByCallerMagnitudes)", Categories = "SetByCaller"))
	TMap<FGameplayTag, float> SetByCallerMagnitudes;

	/**
	 * @brief 이 효과가 스킬 생명주기의 어느 시점에 적용될지 결정하는 조건입니다.
	 * 여러 조건을 체크하면, 해당하는 모든 시점에서 이 효과가 적용될 수 있습니다.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Conditions",
		meta = (Bitmask, BitmaskEnum = "/Script/GGCoreRuntime.ESkillEffectApplyCondition", DisplayName="생명주기 조건"))
	int32 LifecycleConditions = 0;
};

/**
 * @enum ESkillEffectApplyCondition
 * @brief 스킬의 생명주기 중 어느 시점에 GameplayEffect를 적용할지 결정하는 Bitmask Enum입니다.
 */
UENUM(BlueprintType, meta = (Bitflags, UseEnumValuesAsMaskValuesInEditor = "true", DisplayName="스킬 효과 적용 조건"))
enum class ESkillEffectApplyCondition : uint8
{
	None = 0 UMETA(Hidden),

	/** 어빌리티가 활성화될 때 (시전 시작 시) 적용됩니다. */
	OnActivate = 1 << 0 UMETA(DisplayName = "활성화 시"),

	/** 어빌리티가 성공적으로 종료될 때 적용됩니다. */
	OnSuccessfulEnd = 1 << 1 UMETA(DisplayName = "성공적으로 종료 시"),

	/** 어빌리티가 캔슬되었을 때 적용됩니다. */
	OnCancelled = 1 << 2 UMETA(DisplayName = "취소 시"),

	/** 스킬의 핵심 로직이 적용될 때 (예: 타겟 적중 시) 적용됩니다. */
	OnApplyToTarget = 1 << 3 UMETA(DisplayName = "대상에게 적용 시"),
};

ENUM_CLASS_FLAGS(ESkillEffectApplyCondition);

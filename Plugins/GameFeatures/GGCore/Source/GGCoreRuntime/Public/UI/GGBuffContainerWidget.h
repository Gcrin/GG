// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayEffectTypes.h"
#include "AbilitySystemComponent.h"
#include "GGBuffContainerWidget.generated.h"

class UHorizontalBox;
class UGGBuffSlotWidget;
class UGGBuffIconDataAsset;
class ULyraAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FGGStatusEffectMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag EffectTag;

	UPROPERTY(BlueprintReadOnly)
	float Duration = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float RemainingTime = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	bool bIsActive = true;

	FGGStatusEffectMessage()
	{
		EffectTag = FGameplayTag::EmptyTag;
		Duration = 0.0f;
		RemainingTime = 0.0f;
		bIsActive = true;
	}
};

/**
 * 버프/디버프 상태 이펙트를 관리하는 베이스 컨테이너 위젯
 * 파생 클래스에서 ShouldHandleTag()를 구현하여 처리할 태그 타입 결정
 */
UCLASS(Abstract, Blueprintable)
class GGCORERUNTIME_API UGGBuffContainerWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UGGBuffContainerWidget(const FObjectInitializer& ObjectInitializer);

	//~UUserWidget interface
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	//~End of UUserWidget interface

protected:
	/** 처리할 태그들 (블루프린트에서 설정) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StatusEffect")
	FGameplayTagContainer HandledTags;

	/** 이펙트 슬롯들이 들어갈 컨테이너 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHorizontalBox> EffectSlotContainer;

	/** 이펙트 슬롯 위젯 클래스 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StatusEffect")
	TSubclassOf<UGGBuffSlotWidget> EffectSlotWidgetClass;

	/** 이펙트 아이콘 데이터 에셋 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StatusEffect")
	TObjectPtr<UGGBuffIconDataAsset> EffectIconDataAsset;

	/** 최대 표시할 이펙트 개수 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "StatusEffect", meta = (ClampMin = "1", ClampMax = "20"))
	int32 MaxEffectSlots = 10;

	/** 현재 활성화된 이펙트 위젯들 */
	UPROPERTY()
	TArray<TObjectPtr<UGGBuffSlotWidget>> ActiveEffectWidgets;

	/** 표시 대기 중인 이펙트들 */
	UPROPERTY()
	TArray<FGGStatusEffectMessage> PendingEffects;

	/** 추적 중인 GameplayEffect Handle들 */
	UPROPERTY()
	TMap<FGameplayTag, FActiveGameplayEffectHandle> TrackedEffects;

	/** AbilitySystemComponent 캐시 */
	UPROPERTY()
	TWeakObjectPtr<ULyraAbilitySystemComponent> CachedASC;

	/** 마지막 업데이트 시간 */
	float LastUpdateTime = 0.0f;

	/** 업데이트 간격 */
	static constexpr float UpdateInterval = 0.1f;

public:
	/** 이펙트 추가 */
	UFUNCTION(BlueprintCallable, Category = "StatusEffect")
	void AddEffect(const FGGStatusEffectMessage& EffectMessage);

	/** 이펙트 제거 */
	UFUNCTION(BlueprintCallable, Category = "StatusEffect")
	void RemoveEffect(const FGameplayTag& EffectTag);

	/** 모든 이펙트 클리어 */
	UFUNCTION(BlueprintCallable, Category = "StatusEffect")
	void ClearAllEffects();

protected:
	/** 파생 클래스에서 구현: 어떤 태그를 처리할지 결정 */
	bool ShouldHandleTag(const FGameplayTag& Tag) const;

	/** AbilitySystemComponent 가져오기 */
	ULyraAbilitySystemComponent* GetAbilitySystemComponent();

	/** GameplayEffect에서 실시간 데이터 업데이트 */
	void UpdateEffectsFromGameplayEffects();

	/** 특정 이펙트의 현재 상태 가져오기 */
	bool GetEffectCurrentState(const FGameplayTag& EffectTag, float& OutRemainingTime, float& OutDuration);

	/** 새 이펙트 슬롯 위젯 생성 */
	UGGBuffSlotWidget* CreateEffectSlot(const FGGStatusEffectMessage& EffectMessage);

	/** 기존 이펙트 슬롯 찾기 */
	UGGBuffSlotWidget* FindEffectSlot(const FGameplayTag& EffectTag);

	/** 대기 중인 이펙트 슬롯 표시 */
	void ProcessPendingEffects();

	/** 이펙트 슬롯 제거 */
	void RemoveEffectSlot(UGGBuffSlotWidget* SlotWidget);

	/** 슬롯에서 이펙트 만료 이벤트 수신 */
	UFUNCTION()
	void OnSlotEffectExpired(const FGameplayTag& ExpiredEffectTag);

	/** GameplayEffect 추가 감지 */
	UFUNCTION()
	void OnGameplayEffectAdded(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec,
	                           FActiveGameplayEffectHandle Handle);

	/** GameplayEffect 제거 감지 */
	UFUNCTION()
	void OnGameplayEffectRemoved(const FActiveGameplayEffect& RemovedEffect);

	/** GameplayEffect에서 관련 태그 추출 */
	TArray<FGameplayTag> ExtractEffectTagsFromEffect(const FGameplayEffectSpec& Spec) const;

private:
	/** GameplayEffect 델리게이트 핸들들 */
	FDelegateHandle EffectAddedHandle;
	FDelegateHandle EffectRemovedHandle;
};

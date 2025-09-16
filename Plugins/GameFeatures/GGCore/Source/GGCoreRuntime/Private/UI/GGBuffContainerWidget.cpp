// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GGBuffContainerWidget.h"
#include "UI/GGBuffSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Player/GGPlayerState.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GGBuffContainerWidget)

UGGBuffContainerWidget::UGGBuffContainerWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsFocusable(false);
}

void UGGBuffContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if (!IsDesignTime())
	{
		// AbilitySystemComponent 이벤트 바인딩
		if (ULyraAbilitySystemComponent* ASC = GetAbilitySystemComponent())
		{
			// GameplayEffect 추가/제거 이벤트 바인딩
			EffectAddedHandle = ASC->OnActiveGameplayEffectAddedDelegateToSelf.AddUObject(
				this, &UGGBuffContainerWidget::OnGameplayEffectAdded
			);

			EffectRemovedHandle = ASC->OnAnyGameplayEffectRemovedDelegate().AddUObject(
				this, &UGGBuffContainerWidget::OnGameplayEffectRemoved
			);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("ASC is null during construct"));
		}
	}
}

void UGGBuffContainerWidget::NativeDestruct()
{
	if (!IsDesignTime())
	{
		// AbilitySystemComponent 이벤트 해제
		if (ULyraAbilitySystemComponent* ASC = GetAbilitySystemComponent())
		{
			if (EffectAddedHandle.IsValid())
			{
				ASC->OnActiveGameplayEffectAddedDelegateToSelf.Remove(EffectAddedHandle);
			}
			if (EffectRemovedHandle.IsValid())
			{
				ASC->OnAnyGameplayEffectRemovedDelegate().Remove(EffectRemovedHandle);
			}
		}

		ClearAllEffects();
	}

	Super::NativeDestruct();
}

void UGGBuffContainerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (IsDesignTime())
	{
		return;
	}

	LastUpdateTime += InDeltaTime;

	// 주기적으로 GameplayEffect와 동기화
	if (LastUpdateTime >= UpdateInterval)
	{
		UpdateEffectsFromGameplayEffects();
		LastUpdateTime = 0.0f;
	}
}

void UGGBuffContainerWidget::AddEffect(const FGGStatusEffectMessage& EffectMessage)
{
	if (!EffectMessage.EffectTag.IsValid() || !EffectMessage.bIsActive)
	{
		return;
	}

	// 이미 존재하는 이펙트인지 확인
	if (UGGBuffSlotWidget* ExistingSlot = FindEffectSlot(EffectMessage.EffectTag))
	{
		// 기존 이펙트 업데이트
		FBuffDisplayData DisplayData;
		DisplayData.BuffTag = EffectMessage.EffectTag;
		DisplayData.RemainingDuration = EffectMessage.RemainingTime;
		DisplayData.TotalDuration = EffectMessage.Duration;
		DisplayData.bIsActive = true;

		ExistingSlot->SetBuffData(DisplayData);
		return;
	}

	// 최대 슬롯 수 확인
	if (ActiveEffectWidgets.Num() >= MaxEffectSlots)
	{
		UE_LOG(LogTemp, Warning, TEXT("Max effect slots reached (%d), cannot add new effect: %s"),
		       MaxEffectSlots, *EffectMessage.EffectTag.ToString());
		return;
	}

	// 새 이펙트 슬롯 생성
	if (UGGBuffSlotWidget* NewSlot = CreateEffectSlot(EffectMessage))
	{
		ActiveEffectWidgets.Add(NewSlot);
	}
}

void UGGBuffContainerWidget::RemoveEffect(const FGameplayTag& EffectTag)
{
	if (UGGBuffSlotWidget* SlotToRemove = FindEffectSlot(EffectTag))
	{
		RemoveEffectSlot(SlotToRemove);
	}

	// 추적 중인 이펙트에서도 제거
	TrackedEffects.Remove(EffectTag);
}

void UGGBuffContainerWidget::ClearAllEffects()
{
	// 모든 슬롯 위젯 제거
	for (UGGBuffSlotWidget* Widget : ActiveEffectWidgets)
	{
		if (Widget && EffectSlotContainer)
		{
			EffectSlotContainer->RemoveChild(Widget);
		}
	}

	ActiveEffectWidgets.Empty();
	TrackedEffects.Empty();
}

bool UGGBuffContainerWidget::ShouldHandleTag(const FGameplayTag& Tag) const
{
	// 정확히 일치하거나 하위 태그인 경우
	return HandledTags.HasTag(Tag) || HandledTags.HasTagExact(Tag.RequestDirectParent());
}

ULyraAbilitySystemComponent* UGGBuffContainerWidget::GetAbilitySystemComponent()
{
	if (CachedASC.IsValid())
	{
		return CachedASC.Get();
	}

	// PlayerState에서 ASC 가져오기
	if (APlayerController* PC = GetOwningPlayer())
	{
		if (AGGPlayerState* PS = PC->GetPlayerState<AGGPlayerState>())
		{
			CachedASC = Cast<ULyraAbilitySystemComponent>(PS->GetAbilitySystemComponent());
		}
	}

	return CachedASC.Get();
}

void UGGBuffContainerWidget::UpdateEffectsFromGameplayEffects()
{
	ULyraAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC)
	{
		return;
	}

	// 현재 활성 이펙트들의 실시간 상태 업데이트
	for (UGGBuffSlotWidget* SlotWidget : ActiveEffectWidgets)
	{
		if (!SlotWidget || !SlotWidget->IsBuffActive())
		{
			continue;
		}

		const FGameplayTag EffectTag = SlotWidget->GetBuffTag();
		float RemainingTime, Duration;

		if (GetEffectCurrentState(EffectTag, RemainingTime, Duration))
		{
			// 슬롯 위젯의 쿨다운 업데이트
			SlotWidget->UpdateDurationText();

			// 시간이 끝났으면 제거
			if (RemainingTime <= 0.0f)
			{
				RemoveEffect(EffectTag);
			}
		}
		else
		{
			// GameplayEffect가 없으면 이펙트 제거
			RemoveEffect(EffectTag);
		}
	}
}

bool UGGBuffContainerWidget::GetEffectCurrentState(const FGameplayTag& EffectTag, float& OutRemainingTime,
                                                   float& OutDuration)
{
	ULyraAbilitySystemComponent* ASC = GetAbilitySystemComponent();
	if (!ASC)
	{
		return false;
	}

	// 추적 중인 이펙트 핸들로 상태 조회
	if (const FActiveGameplayEffectHandle* Handle = TrackedEffects.Find(EffectTag))
	{
		if (const FActiveGameplayEffect* ActiveEffect = ASC->GetActiveGameplayEffect(*Handle))
		{
			OutDuration = ActiveEffect->GetDuration();
			OutRemainingTime = ActiveEffect->GetTimeRemaining(ASC->GetWorld()->GetTimeSeconds());
			return true;
		}
	}

	return false;
}

UGGBuffSlotWidget* UGGBuffContainerWidget::CreateEffectSlot(const FGGStatusEffectMessage& EffectMessage)
{
	if (!EffectSlotWidgetClass || !EffectSlotContainer)
	{
		return nullptr;
	}

	// 새 슬롯 위젯 생성
	UGGBuffSlotWidget* NewSlot = CreateWidget<UGGBuffSlotWidget>(this, EffectSlotWidgetClass);
	if (!NewSlot)
	{
		return nullptr;
	}

	// 이펙트 데이터 설정
	FBuffDisplayData DisplayData;
	DisplayData.BuffTag = EffectMessage.EffectTag;
	DisplayData.RemainingDuration = EffectMessage.RemainingTime;
	DisplayData.TotalDuration = EffectMessage.Duration;
	DisplayData.bIsActive = true;

	NewSlot->SetBuffData(DisplayData);

	// HorizontalBox에 추가 (자동으로 왼쪽 정렬됨)
	EffectSlotContainer->AddChild(NewSlot);

	return NewSlot;
}

UGGBuffSlotWidget* UGGBuffContainerWidget::FindEffectSlot(const FGameplayTag& EffectTag)
{
	for (UGGBuffSlotWidget* Widget : ActiveEffectWidgets)
	{
		if (Widget && Widget->GetBuffTag() == EffectTag)
		{
			return Widget;
		}
	}
	return nullptr;
}

void UGGBuffContainerWidget::RemoveEffectSlot(UGGBuffSlotWidget* SlotWidget)
{
	if (!SlotWidget || !EffectSlotContainer)
	{
		return;
	}

	// 배열에서 제거
	ActiveEffectWidgets.Remove(SlotWidget);

	// UI에서 제거 (자동으로 왼쪽 정렬됨)
	EffectSlotContainer->RemoveChild(SlotWidget);
}

void UGGBuffContainerWidget::OnSlotEffectExpired(const FGameplayTag& ExpiredEffectTag)
{
	// 슬롯에서 시간 만료 알림을 받으면 제거
	RemoveEffect(ExpiredEffectTag);
}

void UGGBuffContainerWidget::OnGameplayEffectAdded(UAbilitySystemComponent* ASC, const FGameplayEffectSpec& Spec,
                                                   FActiveGameplayEffectHandle Handle)
{
	// GameplayEffect에서 이펙트 관련 태그 추출
	TArray<FGameplayTag> EffectTags = ExtractEffectTagsFromEffect(Spec);

	for (const FGameplayTag& EffectTag : EffectTags)
	{
		// 이펙트 핸들 추적
		TrackedEffects.Add(EffectTag, Handle);

		// 이펙트 메시지 생성해서 추가
		FGGStatusEffectMessage EffectMessage;
		EffectMessage.EffectTag = EffectTag;
		EffectMessage.Duration = Spec.GetDuration();
		EffectMessage.RemainingTime = Spec.GetDuration();
		EffectMessage.bIsActive = true;

		AddEffect(EffectMessage);
	}
}

void UGGBuffContainerWidget::OnGameplayEffectRemoved(const FActiveGameplayEffect& RemovedEffect)
{
	// 제거된 이펙트에서 태그 찾아서 UI에서도 제거
	TArray<FGameplayTag> EffectTags = ExtractEffectTagsFromEffect(RemovedEffect.Spec);

	for (const FGameplayTag& EffectTag : EffectTags)
	{
		RemoveEffect(EffectTag);
	}
}

TArray<FGameplayTag> UGGBuffContainerWidget::ExtractEffectTagsFromEffect(const FGameplayEffectSpec& Spec) const
{
	TArray<FGameplayTag> EffectTags;

	// GameplayEffect의 태그에서 상태 이펙트 태그만 추출
	FGameplayTagContainer AllTags;
	Spec.GetAllAssetTags(AllTags);
	Spec.GetAllGrantedTags(AllTags);

	for (const FGameplayTag& Tag : AllTags)
	{
		if (ShouldHandleTag(Tag))
		{
			EffectTags.Add(Tag);
		}
	}

	return EffectTags;
}

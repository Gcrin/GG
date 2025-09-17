// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GGBuffContainerWidget.h"
#include "UI/GGBuffSlotWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Widgets/SBoxPanel.h"
#include "Components/TextBlock.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "Blueprint/WidgetTree.h"
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

		// 대기열에서 제거
		PendingEffects.RemoveAll([&](const FGGStatusEffectMessage& Pending)
		{
			return Pending.EffectTag == EffectMessage.EffectTag;
		});
		return;
	}

	// 즉시 표시할 수 있는지 확인
	if (ActiveEffectWidgets.Num() < MaxEffectSlots)
	{
		// 새 이펙트 슬롯 생성
		if (UGGBuffSlotWidget* NewSlot = CreateEffectSlot(EffectMessage))
		{
			ActiveEffectWidgets.Add(NewSlot);
		}
	}
	else
	{
		// 대기열에 추가 (중복 체크)
		PendingEffects.RemoveAll([&](const FGGStatusEffectMessage& Pending)
		{
			return Pending.EffectTag == EffectMessage.EffectTag;
		});
		PendingEffects.Add(EffectMessage);

		UE_LOG(LogTemp, Log, TEXT("Effect added to pending queue: %s"),
		       *EffectMessage.EffectTag.ToString());
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
	PendingEffects.Empty();
}

bool UGGBuffContainerWidget::ShouldHandleTag(const FGameplayTag& Tag) const
{
	// 정확히 일치하거나 하위 태그인 경우
	// return HandledTags.HasTag(Tag) || HandledTags.HasTagExact(Tag.RequestDirectParent());
	// HandledTags의 각 태그에 대해 하위 태그인지 확인
	for (const FGameplayTag& HandledTag : HandledTags)
	{
		if (Tag.MatchesTag(HandledTag))
		{
			return true;
		}
	}
	return false;
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

	// 배열 복사해서 사용 (반복 중 배열 변경 방지)
	TArray<TObjectPtr<UGGBuffSlotWidget>> WidgetsCopy = ActiveEffectWidgets;
	// 현재 활성 이펙트들의 실시간 상태 업데이트
	for (UGGBuffSlotWidget* SlotWidget : WidgetsCopy)
	{
		if (!SlotWidget || !SlotWidget->IsBuffActive())
		{
			continue;
		}

		const FGameplayTag EffectTag = SlotWidget->GetBuffTag();
		float RemainingTime, Duration;

		if (GetEffectCurrentState(EffectTag, RemainingTime, Duration))
		{
			// infinite이면 스킵
			if (Duration < 0.0f && RemainingTime < 0.0f) continue;

			// 슬롯 위젯의 쿨다운 업데이트
			SlotWidget->UpdateDurationText(RemainingTime);

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

void UGGBuffContainerWidget::ProcessPendingEffects()
{
	// 표시 가능한 슬롯이 있는 동안 대기 이펙트들을 처리
	while (ActiveEffectWidgets.Num() < MaxEffectSlots && PendingEffects.Num() > 0)
	{
		FGGStatusEffectMessage PendingEffect = PendingEffects[0];
		PendingEffects.RemoveAt(0);

		// 아직 활성 상태인지 확인
		float RemainingTime, Duration;
		if (GetEffectCurrentState(PendingEffect.EffectTag, RemainingTime, Duration))
		{
			// 최신 시간으로 업데이트
			PendingEffect.RemainingTime = RemainingTime;
			PendingEffect.Duration = Duration;

			if (RemainingTime > 0.0f)
			{
				if (UGGBuffSlotWidget* NewSlot = CreateEffectSlot(PendingEffect))
				{
					ActiveEffectWidgets.Add(NewSlot);
					UE_LOG(LogTemp, Log, TEXT("Pending effect now displayed: %s"),
					       *PendingEffect.EffectTag.ToString());
				}
			}
		}
	}
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

	// 대기 중인 이펙트가 있으면 표시
	ProcessPendingEffects();
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
		// 현재 추적 중인 핸들과 제거된 핸들이 같을 때만 UI에서 제거
		if (FActiveGameplayEffectHandle* TrackedHandle = TrackedEffects.Find(EffectTag))
		{
			if (*TrackedHandle == RemovedEffect.Handle)
			{
				// 현재 추적 중인 이펙트가 제거되었으므로 UI에서도 제거
				RemoveEffect(EffectTag);
			}
			// else: 다른 핸들이 제거된 것이므로 UI는 그대로 유지
		}
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
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Tag: %s"), *Tag.ToString());
		}
	}

	return EffectTags;
}

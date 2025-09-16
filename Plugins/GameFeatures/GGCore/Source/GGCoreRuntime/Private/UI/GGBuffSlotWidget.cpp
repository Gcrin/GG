// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GGBuffSlotWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Overlay.h"
#include "Components/Border.h"
#include "Engine/Texture2D.h"
#include "UI/GGBuffIconDataAsset.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GGBuffSlotWidget)

UGGBuffSlotWidget::UGGBuffSlotWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SetIsFocusable(false);
}

void UGGBuffSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 초기 상태를 빈 슬롯으로 설정
	ClearBuff();
}

void UGGBuffSlotWidget::SetBuffData(const FBuffDisplayData& InBuffData)
{
	BuffData = InBuffData;

	if (BuffData.bIsActive)
	{
		// UI 요소들 업데이트
		UpdateBuffIcon();
		// UpdateStackText();
		UpdateDurationText();
		UpdateBorderColor();

		// 슬롯 표시
		if (BuffOverlay)
		{
			BuffOverlay->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else
	{
		ClearBuff();
	}

	// 블루프린트에서 추가 처리할 수 있도록 이벤트 호출
	OnBuffDataChanged(BuffData);
}

void UGGBuffSlotWidget::ClearBuff()
{
	BuffData = FBuffDisplayData(); // 기본값으로 초기화

	// 슬롯 숨김
	if (BuffOverlay)
	{
		BuffOverlay->SetVisibility(EmptySlotVisibility);
	}

	// 아이콘 클리어
	if (BuffIcon)
	{
		BuffIcon->SetBrushFromTexture(nullptr);
	}

	if (DurationText)
	{
		DurationText->SetText(FText::GetEmpty());
	}

	// 블루프린트 이벤트 호출
	OnBuffDataChanged(BuffData);
}

void UGGBuffSlotWidget::UpdateBuffIcon()
{
	if (!BuffIcon || !BuffIconDataAsset || !BuffData.BuffTag.IsValid())
	{
		return;
	}

	// 데이터 에셋에서 아이콘 찾기
	if (UTexture2D* IconTexture = BuffIconDataAsset->GetBuffIcon(BuffData.BuffTag))
	{
		BuffIcon->SetBrushFromTexture(IconTexture);
	}
}

void UGGBuffSlotWidget::UpdateDurationText()
{
	if (!DurationText)
	{
		return;
	}

	if (BuffData.TotalDuration <= 0.0f && bHideDurationForPermanent)
	{
		// 지속시간이 무한인 경우 숨김
		DurationText->SetVisibility(ESlateVisibility::Hidden);
		return;
	}

	if (BuffData.RemainingDuration > 0.0f)
	{
		const FString DurationString = FormatDurationText(BuffData.RemainingDuration);
		DurationText->SetText(FText::FromString(DurationString));
		DurationText->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		DurationText->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UGGBuffSlotWidget::UpdateBorderColor()
{
	if (!TypeBorder)
	{
		return;
	}

	const FLinearColor BorderColor = BuffData.bIsBuff ? BuffBorderColor : DebuffBorderColor;
	TypeBorder->SetBrushColor(BorderColor);
}

FString UGGBuffSlotWidget::FormatDurationText(float Duration) const
{
	if (Duration <= 0.0f)
	{
		return TEXT("");
	}

	const int32 Minutes = FMath::FloorToInt(Duration / 60.0f);
	const int32 Seconds = FMath::FloorToInt(Duration) % 60;

	if (Minutes > 0)
	{
		return FString::Printf(TEXT("%d:%02d"), Minutes, Seconds);
	}
	else if (Seconds >= 10)
	{
		return FString::Printf(TEXT("%ds"), Seconds);
	}
	else
	{
		// 10초 미만일 때는 소수점 표시
		return FString::Printf(TEXT("%.1fs"), Duration);
	}
}

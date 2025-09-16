// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "GameplayTagContainer.h"
#include "GGBuffSlotWidget.generated.h"

/**
 * 
 */
class UImage;
class UTextBlock;
class UProgressBar;
class UOverlay;
class UBorder;

USTRUCT(BlueprintType)
struct FBuffDisplayData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag BuffTag;

	UPROPERTY(BlueprintReadOnly)
	float RemainingDuration = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	float TotalDuration = 0.0f;

	UPROPERTY(BlueprintReadOnly)
	bool bIsActive = false;

	UPROPERTY(BlueprintReadOnly)
	bool bIsBuff = true; // true = 버프, false = 디버프

	FBuffDisplayData()
	{
		BuffTag = FGameplayTag::EmptyTag;
	}
};

/**
 * 개별 버프/디버프 아이콘을 표시하는 슬롯 위젯
 * 쿨다운, 스택 카운트, 버프/디버프 구분 등을 처리
 */
UCLASS(Abstract, Blueprintable)
class GGCORERUNTIME_API UGGBuffSlotWidget : public UCommonUserWidget
{
	GENERATED_BODY()

public:
	UGGBuffSlotWidget(const FObjectInitializer& ObjectInitializer);

	//~UUserWidget interface
	virtual void NativeConstruct() override;
	//~End of UUserWidget interface

	/** 버프 데이터 설정 */
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void SetBuffData(const FBuffDisplayData& InBuffData);

	/** 버프 클리어 */
	UFUNCTION(BlueprintCallable, Category = "Buff")
	void ClearBuff();

	/** 지속시간 텍스트 업데이트 */
	void UpdateDurationText();

	/** 현재 버프가 활성 상태인지 */
	UFUNCTION(BlueprintPure, Category = "Buff")
	bool IsBuffActive() const { return BuffData.bIsActive; }

	/** 현재 버프 태그 반환 */
	UFUNCTION(BlueprintPure, Category = "Buff")
	FGameplayTag GetBuffTag() const { return BuffData.BuffTag; }

protected:
	/** 메인 컨테이너 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOverlay> BuffOverlay;

	/** 버프 아이콘 이미지 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> BuffIcon;

	/** 남은 시간 텍스트 (옵션) */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> DurationText;

	/** 버프/디버프 구분용 테두리 */
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> TypeBorder;

	/** 현재 버프 데이터 */
	UPROPERTY(BlueprintReadOnly, Category = "Buff")
	FBuffDisplayData BuffData;

	/** 버프 아이콘 데이터 에셋 참조 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff")
	TObjectPtr<class UGGBuffIconDataAsset> BuffIconDataAsset;

	/** 빈 슬롯일 때의 가시성 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	ESlateVisibility EmptySlotVisibility = ESlateVisibility::Hidden;

	/** 버프 테두리 색상 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	FLinearColor BuffBorderColor = FLinearColor::Green;

	/** 디버프 테두리 색상 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	FLinearColor DebuffBorderColor = FLinearColor::Red;

	/** 지속시간이 무한일 때 시간 텍스트 숨기기 여부 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	bool bHideDurationForPermanent = true;

protected:
	/** UI 업데이트 */
	UFUNCTION(BlueprintImplementableEvent, Category = "Buff")
	void OnBuffDataChanged(const FBuffDisplayData& NewBuffData);

	/** 아이콘 설정 */
	void UpdateBuffIcon();

	/** 테두리 색상 업데이트 */
	void UpdateBorderColor();

	/** 시간을 문자열로 포맷 (예: 1:23, 59s) */
	FString FormatDurationText(float Duration) const;
};

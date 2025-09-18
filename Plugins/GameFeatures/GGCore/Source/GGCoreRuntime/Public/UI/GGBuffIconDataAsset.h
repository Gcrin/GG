// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Engine/Texture2D.h"
#include "GGBuffIconDataAsset.generated.h"

/**
 * 버프/디버프 아이콘들을 관리하는 데이터 에셋
 * GameplayTag를 키로 사용하여 각 버프의 아이콘 정보를 저장
 */
UCLASS(BlueprintType)
class GGCORERUNTIME_API UGGBuffIconDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	UGGBuffIconDataAsset();

protected:
	/** GameplayTag를 키로 하는 버프 아이콘 맵 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Buff Icons")
	TMap<FGameplayTag, TObjectPtr<UTexture2D>> BuffIconMap;

public:
	/** 특정 태그의 버프 아이콘 데이터 가져오기 */
	UFUNCTION(BlueprintCallable, Category = "Buff Icons")
	UTexture2D* GetBuffIcon(const FGameplayTag& BuffTag) const;
};

// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GGBuffIconDataAsset.h"
#include "Engine/Texture2D.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(GGBuffIconDataAsset)

UGGBuffIconDataAsset::UGGBuffIconDataAsset()
{
	// 기본값 설정은 생성자에서
}

UTexture2D* UGGBuffIconDataAsset::GetBuffIcon(const FGameplayTag& BuffTag) const
{
	if (!BuffTag.IsValid())
	{
		return nullptr;
	}

	if (const TObjectPtr<UTexture2D>* IconTexture = BuffIconMap.Find(BuffTag))
	{
		return IconTexture->Get();
	}
	
	UE_LOG(LogTemp, Warning, TEXT("태그에 매칭된 버프 아이콘을 찾을 수 없습니다. 태그: %s"), *BuffTag.ToString());
	
	return nullptr;
}

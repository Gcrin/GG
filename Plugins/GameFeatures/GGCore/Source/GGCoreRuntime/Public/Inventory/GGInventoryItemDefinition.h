// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GGInventoryItemDefinition.generated.h"

UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class UGGInventoryItemFragment : public UObject
{
	GENERATED_BODY()
	
public:
};

/**
 * 
 */
UCLASS(Blueprintable)
class GGCORERUNTIME_API UGGInventoryItemDefinition : public UObject
{
	GENERATED_BODY()

public:
	UGGInventoryItemDefinition(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	const UGGInventoryItemFragment* FindFragmentByClass(TSubclassOf<UGGInventoryItemFragment> FragmentClass) const;
	
	/* Inventory Item 정의(메타) 이름 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
	FText DisplayName;
	
	/* 아이템이 어떤 특성(Fragment)들로 구성되어 있는지 담는 배열 */
	UPROPERTY(EditDefaultsOnly, Instanced, BlueprintReadOnly, Category = Display)
	TArray<TObjectPtr<UGGInventoryItemFragment>> Fragments;
};

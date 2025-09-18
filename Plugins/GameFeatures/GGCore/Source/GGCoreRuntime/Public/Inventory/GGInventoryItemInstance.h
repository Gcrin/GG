// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GGInventoryItemInstance.generated.h"

class UGGInventoryItemDefinition;

/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API UGGInventoryItemInstance : public UObject
{
	GENERATED_BODY()

public:
	UGGInventoryItemInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Inventory Item의 정의, 실제 객체가 아니라 '설계도'나 '타입' 정보를 담음
	UPROPERTY()
	TSubclassOf<UGGInventoryItemDefinition> ItemDef;
};

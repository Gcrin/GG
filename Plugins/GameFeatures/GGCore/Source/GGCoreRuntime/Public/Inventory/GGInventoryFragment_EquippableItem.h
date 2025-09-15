// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Inventory/GGInventoryItemDefinition.h"
#include "Templates/SubclassOf.h"
#include "GGInventoryFragment_EquippableItem.generated.h"

UCLASS()
class UGGInventoryFragment_EquippableItem : public UGGInventoryItemFragment
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category = GG)
	TSubclassOf<UGGEquipmentDefinition> EquipmentDefinition;
	
};
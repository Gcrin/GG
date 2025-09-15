// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/GGInventoryItemInstance.h"
#include "Inventory/GGInventoryItemDefinition.h"

UGGInventoryItemInstance::UGGInventoryItemInstance(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}


const UGGInventoryItemFragment* UGGInventoryItemInstance::FindFragmentByClass(
	TSubclassOf<UGGInventoryItemFragment> FragmentClass) const
{
	if((ItemDef != nullptr) && (FragmentClass != nullptr))
	{
		// Fragment 정보는 Instance가 아닌 Definition에 있다
		return GetDefault<UGGInventoryItemDefinition>(ItemDef)->FindFragmentByClass(FragmentClass);
	}
	return nullptr;
}
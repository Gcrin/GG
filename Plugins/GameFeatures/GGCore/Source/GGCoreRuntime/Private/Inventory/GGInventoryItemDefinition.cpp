// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/GGInventoryItemDefinition.h"

UGGInventoryItemDefinition::UGGInventoryItemDefinition(const FObjectInitializer& ObjectInitializer)
{
}

const UGGInventoryItemFragment* UGGInventoryItemDefinition::FindFragmentByClass(
	TSubclassOf<UGGInventoryItemFragment> FragmentClass) const
{
	if(FragmentClass)
	{
		//Fragment를 순회하며, IsA()를 통해 해당 클래스를 가지고 있는지 확인
		for(UGGInventoryItemFragment* Fragment : Fragments)
		{
			if(Fragment && Fragment->IsA(FragmentClass))
			{
				return Fragment;
			}
		}
	}
	return nullptr;
}

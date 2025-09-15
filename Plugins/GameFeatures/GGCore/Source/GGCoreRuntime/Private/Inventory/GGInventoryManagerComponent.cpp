// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/GGInventoryManagerComponent.h"
#include "Equipment/GGEquipmentManagerComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Inventory/GGInventoryItemInstance.h"

UGGInventoryManagerComponent::UGGInventoryManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventoryList(this)
{}

void UGGInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	
	if (AController* OwnerController = GetOwner<AController>())
	{
		if (APawn* OwnerPawn = OwnerController->GetPawn())
		{
			// Pawn에서 EquipmetComponent 캐싱
			CachedEquipmentComponent = OwnerPawn->FindComponentByClass<UGGEquipmentManagerComponent>();
		}
	}
	
}

/*void UGGInventoryManagerComponent::EquipItemByIndex(int32 ItemIndex)
{
	// 1. 장비 컴포넌트를 찾았는지 확인
	if (CachedEquipmentComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("CachedEquipmentComponent is null."));
		return;
	}

	// 2. 인벤토리 목록에서 해당 인덱스의 아이템을 가져옵니다.
	if (InventoryList.Entries.IsValidIndex(ItemIndex))
	{
		UGGInventoryItemInstance* ItemToEquip = InventoryList.Entries[ItemIndex].Instance;
		if (ItemToEquip)
		{
			// 3. 장비 컴포넌트에게 장착 명령!
			UE_LOG(LogTemp, Log, TEXT("Equipping item: %s"), *GetNameSafe(ItemToEquip));
			CachedEquipmentComponent->EquipItem(ItemToEquip);
		}
	}
}

void UGGInventoryManagerComponent::UnequipCurrentItem()
{
	if (CachedEquipmentComponent)
	{
		if(const UGGEquipmentInstance* FirstEquipped = CachedEquipmentComponent->GetFirstEquippedItem())
		{
			// 현재 장착된 아이템을 해제하도록 명령합니다.
			CachedEquipmentComponent->UnequipItem(FirstEquipped->GetInstigator());
		}
	}
}*/
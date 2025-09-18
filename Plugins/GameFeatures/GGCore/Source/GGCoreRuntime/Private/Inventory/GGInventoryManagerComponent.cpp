// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/GGInventoryManagerComponent.h"
#include "Equipment/GGEquipmentManagerComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
#include "Inventory/GGInventoryItemInstance.h"
#include "Inventory/GGInventoryItemDefinition.h"
#include "Inventory/GGInventoryItemInstance.h"

UGGInventoryItemInstance* FGGInventoryList::AddEntry(TSubclassOf<UGGInventoryItemDefinition> ItemDef)
{
	UGGInventoryItemInstance* Result = nullptr;
	check(ItemDef);
	check(OwnerComponent);
	
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	
	FGGInventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Instance = NewObject<UGGInventoryItemInstance>(OwningActor);
	NewEntry.Instance->ItemDef = ItemDef;
	
	Result = NewEntry.Instance;
	return Result;
}

UGGInventoryManagerComponent::UGGInventoryManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventoryList(this)
{}

UGGInventoryItemInstance* UGGInventoryManagerComponent::AddItemDefinition(
	TSubclassOf<UGGInventoryItemDefinition> ItemDef)
{
	UGGInventoryItemInstance* Result = nullptr;
	if(ItemDef)
	{
		Result = InventoryList.AddEntry(ItemDef);
	}
	return Result;
}

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

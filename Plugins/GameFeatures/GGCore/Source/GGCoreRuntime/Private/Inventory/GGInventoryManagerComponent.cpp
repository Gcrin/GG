// Fill out your copyright notice in the Description page of Project Settings.


#include "Inventory/GGInventoryManagerComponent.h"

UGGInventoryManagerComponent::UGGInventoryManagerComponent(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
	, InventoryList(this)
{}

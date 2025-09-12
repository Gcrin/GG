// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGInventoryManagerComponent.generated.h"


/* forward declarations */
class UGGInventoryItemInstance;
class UGGInventoryItemDefinition;

/* Inventory Item 단위 객체 */
USTRUCT(BlueprintType)
struct FGGInventoryEntry
{
	GENERATED_BODY()
	
	UPROPERTY()
	TObjectPtr<UGGInventoryItemInstance> Instance = nullptr;
};

/* Inventory Item 관리 객체 */
USTRUCT(BlueprintType)
struct FGGInventoryList
{
	GENERATED_BODY()
	
	FGGInventoryList(UActorComponent* InOwnerComponent = nullptr)
		: OwnerComponent(InOwnerComponent)
	{}
	
	UPROPERTY()
	TArray<FGGInventoryEntry> Entries;
	
	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};

/* 
* PlayerController의 Component로서 Inventory를 관리한다
*/
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GGCORERUNTIME_API UGGInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UGGInventoryManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UPROPERTY()
	FGGInventoryList InventoryList;
};

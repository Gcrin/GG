// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GGInventoryManagerComponent.generated.h"


/* forward declarations */
class UGGInventoryItemInstance;
class UGGInventoryItemDefinition;
class UGGEquipmentManagerComponent;

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

	UGGInventoryItemInstance* AddEntry(TSubclassOf<UGGInventoryItemDefinition> ItemDef);
	
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

	UFUNCTION(BlueprintCallable, Category = Inventory)
	UGGInventoryItemInstance* AddItemDefinition(TSubclassOf<UGGInventoryItemDefinition> ItemDef);
	
	UPROPERTY()
	FGGInventoryList InventoryList;

	/*// 외부에 공개할 장착/해제 함수들을 선언
	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void EquipItemByIndex(int32 ItemIndex);

	UFUNCTION(BlueprintCallable, Category = "Inventory")
	void UnequipCurrentItem();*/

protected:
	// 게임 시작시 초기화 용
	virtual void BeginPlay() override;

private:
	// EquipmentComponent를 저장해 둘 포인터 변수
	UPROPERTY()
	TObjectPtr<UGGEquipmentManagerComponent> CachedEquipmentComponent;

};

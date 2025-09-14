// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "GGEquipmentManagerComponent.generated.h"

class UGGEquipmentDefinition;
class UGGEquipmentInstance;

USTRUCT(BlueprintType)
struct FGGAppliedEquipmentEntry
{
	GENERATED_BODY()
	
	/** 장착물에 대한 메다 데이터 */
	UPROPERTY()
	TSubclassOf<UGGEquipmentDefinition> EquipmentDefinition;
	
	/* EquipmentDefinition을 통해 생성되는 인스턴스 */
	UPROPERTY()
	TObjectPtr<UGGEquipmentInstance> Instance = nullptr;
};

/*
* EquipmentInstance의 인스턴스를 Entry에서 관리
*/
USTRUCT(BlueprintType)
struct FGGEquipmentList
{
	GENERATED_BODY()
	
	FGGEquipmentList(UActorComponent* InOwnerComponent = nullptr)
		: OwnerComponent(InOwnerComponent)
	{}
	
	/** 장착물에 대한 관리 리스트 */
	UPROPERTY()
	TArray<FGGAppliedEquipmentEntry> Entries;
	
	UPROPERTY()
	TObjectPtr<UActorComponent> OwnerComponent;
};

/*
* Pawn의 Component로써 장착물에 대한 관리를 담당
*/
UCLASS()
class GGCORERUNTIME_API UGGEquipmentManagerComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	UGGEquipmentManagerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	
	UPROPERTY()
	FGGEquipmentList EquipmentList;
};
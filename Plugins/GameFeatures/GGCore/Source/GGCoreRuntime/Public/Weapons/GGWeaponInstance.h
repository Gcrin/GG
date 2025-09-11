// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Equipment/GGEquipmentInstance.h"
#include "GGWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API UGGWeaponInstance : public UGGEquipmentInstance
{
	GENERATED_BODY()

public:
	UGGWeaponInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	/* CosmeticAnimationTypes이 만들어지면 추가? 애니메이션용 */
	
	/** Weapon에 Equip/UnEquip에 대한 Animation Set 정보를 들고 있다 **/
	//장착했을때 애니메이션 레이어
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	//FHakAnimLayerSelectionSet EquippedAnimSet;
	
	//장착을 해재할 때 애니메이션 레이어
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	//FHakAnimLayerSelectionSet UnequippedAnimSet;
	
};

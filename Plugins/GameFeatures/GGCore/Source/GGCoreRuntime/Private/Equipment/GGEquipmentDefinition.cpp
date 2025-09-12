// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/GGEquipmentDefinition.h"
#include "Equipment/GGEquipmentInstance.h"

UGGEquipmentDefinition::UGGEquipmentDefinition(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	//기본값으로, GGEquipmentInstance로 설정
	InstanceType = UGGEquipmentInstance::StaticClass();
}
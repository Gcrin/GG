// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GGPlayerState.h"

#include "AbilitySystem/Attributes/GGDefenseSet.h"
#include "AbilitySystem/Attributes/GGOffenseSet.h"
#include "AbilitySystem/Attributes/GGResourceSet.h"
#include "AbilitySystem/Attributes/GGUtilitySet.h"

AGGPlayerState::AGGPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ResourceSet = CreateDefaultSubobject<UGGResourceSet>(TEXT("ResourceSet"));
	OffenseSet = CreateDefaultSubobject<UGGOffenseSet>(TEXT("OffenseSet"));
	DefenseSet = CreateDefaultSubobject<UGGDefenseSet>(TEXT("DefenseSet"));
	UtilitySet = CreateDefaultSubobject<UGGUtilitySet>(TEXT("UtilitySet"));
}

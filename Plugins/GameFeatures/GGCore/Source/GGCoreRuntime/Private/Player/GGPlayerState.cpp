// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GGPlayerState.h"

#include "AbilitySystem/Attributes/GGResourceSet.h"

AGGPlayerState::AGGPlayerState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ResourceSet = CreateDefaultSubobject<UGGResourceSet>(TEXT("ResourceSet"));
}

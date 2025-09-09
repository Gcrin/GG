// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/GGCharacter.h"

#include "Character/GGResourceComponent.h"

AGGCharacter::AGGCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ResourceComponent = CreateDefaultSubobject<UGGResourceComponent>(TEXT("ResourceComponent"));
}

void AGGCharacter::OnAbilitySystemInitialized()
{
	Super::OnAbilitySystemInitialized();

	ULyraAbilitySystemComponent* LyraASC = GetLyraAbilitySystemComponent();
	check(LyraASC);
	
	ResourceComponent->InitializeWithAbilitySystem(LyraASC);
}

void AGGCharacter::OnAbilitySystemUninitialized()
{
	Super::OnAbilitySystemUninitialized();

	ResourceComponent->UninitializeFromAbilitySystem();
}

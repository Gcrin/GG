// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/LyraCharacter.h"
#include "GGCharacter.generated.h"

class UGGResourceComponent;
/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API AGGCharacter : public ALyraCharacter
{
	GENERATED_BODY()
	
public:
	
	AGGCharacter(const FObjectInitializer& ObjectInitializer);

protected:
	
	virtual void OnAbilitySystemInitialized() override;
	virtual void OnAbilitySystemUninitialized() override;
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GG|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UGGResourceComponent> ResourceComponent;
};

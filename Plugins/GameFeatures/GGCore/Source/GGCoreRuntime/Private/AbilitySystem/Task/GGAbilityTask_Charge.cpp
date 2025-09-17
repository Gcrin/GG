// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Task/GGAbilityTask_Charge.h"

#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/GGSkillAbility.h"

UGGAbilityTask_Charge* UGGAbilityTask_Charge::ChargeSkill(
	UGameplayAbility* OwningAbility,
	float MaxChargeTime,
	float MinChargePercent)
{
	UGGAbilityTask_Charge* Task = NewAbilityTask<UGGAbilityTask_Charge>(OwningAbility);
	Task->MaxChargeTime = MaxChargeTime;
	Task->MinChargePercent = MinChargePercent;

	Task->SkillIdentityTag = FGameplayTag();

	if (UGGSkillAbility* SkillAbility = Cast<UGGSkillAbility>(OwningAbility))
	{
		if (UGGSkillDataBase* SkillData = SkillAbility->GetSkillData())
		{
			Task->SkillIdentityTag = SkillData->SkillIdentityTag;
		}
	}

	return Task;
}

void UGGAbilityTask_Charge::Activate()
{
	Super::Activate();

	CurrentChargeTime = 0.0f;

	// 차지 시작
	bIsCharging = true;
}

void UGGAbilityTask_Charge::TickTask(float DeltaTime)
{
	if (!bIsCharging)
		return;

	// 차지 진행
	CurrentChargeTime += DeltaTime;
	float ChargePercent = GetCurrentChargePercent();
	OnChargeUpdate.Broadcast(ChargePercent);

	if (!bHasMinChargeSucceeded && ChargePercent >= MinChargePercent)
	{
		bHasMinChargeSucceeded = true;
		OnMinChargeSucceeded.Broadcast(ChargePercent);
	}

	// 풀 차지 완료
	if (ChargePercent >= 1.0f)
	{
		HandleChargeComplete();
	}
}

void UGGAbilityTask_Charge::OnDestroy(bool bInOwnerFinished)
{
	bIsCharging = false;
	Super::OnDestroy(bInOwnerFinished);
}

void UGGAbilityTask_Charge::HandleChargeComplete()
{
	if (!bIsCharging) return;

	bIsCharging = false;
	OnMaxChargeComplete.Broadcast(1.0f);
	EndTask();
}

float UGGAbilityTask_Charge::GetCurrentChargePercent() const
{
	return FMath::Clamp(CurrentChargeTime / MaxChargeTime, 0.0f, 1.0f);
}

void UGGAbilityTask_Charge::HandleChargeReleased()
{
	if (!bIsCharging) return;

	bIsCharging = false;
	float ChargePercent = GetCurrentChargePercent();
	OnChargeReleased.Broadcast(ChargePercent);
	EndTask();
}

void UGGAbilityTask_Charge::HandleChargeCancelled()
{
	if (!bIsCharging) return;

	bIsCharging = false;
	float ChargePercent = GetCurrentChargePercent();
	OnChargeCancelled.Broadcast(ChargePercent);
	EndTask();
}

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GGAbilityTask_Charge.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChargeDelegate, float, ChargePercent);

/**
 * 
 */
UCLASS()
class GGCORERUNTIME_API UGGAbilityTask_Charge : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "GG|Ability|Tasks",
		meta = (HidePin = "OwningAbility", DefaultToSelf = "OwningAbility", BlueprintInternalUseOnly = "TRUE"))
	static UGGAbilityTask_Charge* ChargeSkill(
		UGameplayAbility* OwningAbility,
		float MaxChargeTime,
		float MinChargePercent = 1.0f
	);

	/** 중간에 입력 해제 */
	UFUNCTION(BlueprintCallable, Category = "GG|Ability|Tasks")
	void HandleChargeReleased();

	/** 피격 등으로 차지 취소 */
	UFUNCTION(BlueprintCallable, Category = "GG|Ability|Tasks")
	void HandleChargeCancelled();

	/** 차지 진행률이 업데이트될 때마다 호출됩니다. */
	UPROPERTY(BlueprintAssignable)
	FChargeDelegate OnChargeUpdate;

	/** 풀 차지가 완료되는 순간 호출됩니다. */
	UPROPERTY(BlueprintAssignable)
	FChargeDelegate OnMaxChargeComplete;

	/** 최소 차지 조건을 만족하는 순간 호출됩니다. */
	UPROPERTY(BlueprintAssignable)
	FChargeDelegate OnMinChargeSucceeded;

	/** 플레이어가 입력을 떼었을 때 호출됩니다. (성공/실패 여부와 관계없이) */
	UPROPERTY(BlueprintAssignable)
	FChargeDelegate OnChargeReleased;

	/** 어빌리티가 외부 요인으로 취소되었을 때 호출됩니다. */
	UPROPERTY(BlueprintAssignable)
	FChargeDelegate OnChargeCancelled;

protected:
	virtual void Activate() override;
	virtual void TickTask(float DeltaTime) override;
	virtual void OnDestroy(bool bInOwnerFinished) override;

private:
	/** 풀 차지 완료 */
	void HandleChargeComplete();
	float GetCurrentChargePercent() const;

	float MaxChargeTime = 1.0f;
	float CurrentChargeTime = 0.0f;
	float MinChargePercent = 1.0f;
	bool bIsCharging = false;
	bool bHasMinChargeSucceeded = false;
	FGameplayTag SkillIdentityTag;
};

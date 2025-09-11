// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/GGGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemGlobals.h"
#include "AbilitySystem/LyraAbilitySystemComponent.h"
#include "AbilitySystem/Data/GGSkillDataBase.h"

void UGGGameplayAbility::ApplyEffectsByCondition(ESkillEffectApplyCondition Condition, AActor* Target)
{
	if (!SkillData) return;

	ULyraAbilitySystemComponent* SourceASC = GetLyraAbilitySystemComponentFromActorInfo();

	AActor* TargetActor = Target ? Target : GetAvatarActorFromActorInfo();
	ULyraAbilitySystemComponent* TargetASC =
		Cast<ULyraAbilitySystemComponent>(UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(TargetActor));

	if (!SourceASC || !TargetASC)
	{
		return;
	}

	TArray<FGameplayEffectSpecHandle> Specs = CreateEffectSpecsByCondition(Condition);

	for (const FGameplayEffectSpecHandle& SpecHandle : Specs)
	{
		if (SpecHandle.IsValid())
		{
			SourceASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data.Get(), TargetASC);
		}
	}
}

TArray<FGameplayEffectSpecHandle> UGGGameplayAbility::CreateEffectSpecsByCondition(ESkillEffectApplyCondition Condition)
{
	TArray<FGameplayEffectSpecHandle> OutSpecs;

	ULyraAbilitySystemComponent* SourceASC = GetLyraAbilitySystemComponentFromActorInfo();
	if (!SkillData || !SourceASC)
	{
		return OutSpecs;
	}

	const FGameplayAbilitySpecHandle GameplayAbilitySpecHandle = GetCurrentAbilitySpecHandle();
	const FGameplayAbilityActorInfo* ActorInfo = GetCurrentActorInfo();

	FGameplayEffectContextHandle ContextHandle = MakeEffectContext(GameplayAbilitySpecHandle, ActorInfo);

	// 스킬 데이터의 모든 GameplayEffects를 순회합니다.
	for (const FSkillEffectData& EffectData : SkillData->GameplayEffects)
	{
		// 생명주기 조건이 일치하고, Effect 클래스가 유효한지 확인합니다.
		if (EffectData.EffectClass &&
			EnumHasAllFlags(static_cast<ESkillEffectApplyCondition>(EffectData.LifecycleConditions), Condition))
		{
			// Spec을 생성합니다.
			FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(
				EffectData.EffectClass, GetAbilityLevel(), ContextHandle);

			if (SpecHandle.IsValid())
			{
				// 데이터 애셋에 정의된 SetByCaller 값들을 Spec에 주입합니다.
				for (const auto& Elem : EffectData.SetByCallerMagnitudes)
				{
					SpecHandle.Data->SetSetByCallerMagnitude(Elem.Key, Elem.Value);
				}

				// 완성된 Spec을 결과 배열에 추가합니다.
				OutSpecs.Add(SpecHandle);
			}
		}
	}

	return OutSpecs;
}

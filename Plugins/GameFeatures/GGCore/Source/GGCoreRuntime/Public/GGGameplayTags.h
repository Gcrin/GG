// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace GGGameplayTags
{
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_Physical);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Type_Magic);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_SkillDamage);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_SkillDamage_Multiplier);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Cooldown_Duration);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Resource_Mana);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Resource_Stamina);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Resource_Health);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(SetByCaller_Heal);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Combat_DamageDealt);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Combat_DamageDealt_Physical);
	UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Combat_DamageDealt_Magic);
};

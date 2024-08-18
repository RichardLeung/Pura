﻿#pragma once

#include "NativeGameplayTags.h"

namespace PuraGameplayTags
{
	// Input Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);

	// Ability Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	// Event Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);

	// Status Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
}

#pragma once

#include "NativeGameplayTags.h"

namespace PuraGameplayTags
{
	//Player Input Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_EquipAxe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_UnequipAxe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_LightAttack_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack_Axe);

	//Player Ability Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);

	//Player Event Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);

	//Player Status Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);

	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	//Enemy Ability Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	//Shared Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);

	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);
}

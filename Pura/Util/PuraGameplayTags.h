﻿#pragma once

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
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Roll);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SwitchTarget)
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Block);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable)
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock)

	//Player Ability Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Roll);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_TargetLock);
	
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);
	
	//Player Event Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SuccessfulBlock);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Left);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Right);
	
	//Player Status Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rolling);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Blocking);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_TargetLock);

	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	//Enemy Ability Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);

	//Enemy Status Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
	
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Weapon);

	//Shared Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_HitReact);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Ability_Death);
	
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_MeleeHit);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_HitReact);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Event_SpawnProjectile);
	
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_SetByCaller_BaseDamage);

	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Dead);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Front);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Back);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Left);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_HitReact_Right);
}

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
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SwitchTarget);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_MustBeHeld_Block);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_Rage);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Light);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialWeaponAbility_Heavy);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_PickUp_Stone);

	//Player Ability Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Equip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Unequip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Light_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Attack_Heavy_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_HitPause);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Roll);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Block);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_TargetLock);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_Rage);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Light);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_SpecialWeaponAbility_Heavy);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Ability_PickUp_Stone);

	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Light);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Cooldown_SpecialWeaponAbility_Heavy);
	
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Weapon_Axe);
	
	//Player Event Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Equip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_Unequip_Axe);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_HitPause);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SuccessfulBlock);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Left);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_SwitchTarget_Right);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ActivateRage);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_AOE);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Event_ConsumeStone)
	
	//Player Status Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_JumpToFinisher);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rolling);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Blocking);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_TargetLock);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Activating);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Active);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_Full);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Rage_None);

	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Spirit_Active);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Spirit_Full);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_Status_Spirit_None);
	
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Light);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Player_SetByCaller_AttackType_Heavy);

	//Enemy Ability Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Melee);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_Ranged);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SummonEnemies);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Ability_SpawnStone)

	//Enemy Event Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Event_SummonEnemies);

	//Enemy Status Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Strafing);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_UnderAttack);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Enemy_Status_Unblockable)
	
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
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Shared_Status_Invincible);

	// Game Data Tags
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_MainMenu);
	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_Level_SurvivalGameMode);

	PURA_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(GameData_SaveGame_Slot_1);
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCombatComponent.h"

#include "Pura/Item/Weapon/PuraHeroWeapon.h"

APuraHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APuraHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

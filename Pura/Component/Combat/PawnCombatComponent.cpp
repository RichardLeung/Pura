// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnCombatComponent.h"
#include "Pura/Item/Weapon/PuraBaseWeapon.h"
#include "Pura/Util/PuraDebugHelper.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
                                                 APuraBaseWeapon* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("%s has already been added"), *InWeaponToRegister->GetName());
	check(InWeaponToRegister);
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	FString DebugMessage = FString::Printf(TEXT("Weapon %s has been registered to %s"), *InWeaponToRegister->GetName(), *GetOwner()->GetName());
	Debug::Print(DebugMessage);
	if(bRegisterAsEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTagToRegister;
	}
}

APuraBaseWeapon* UPawnCombatComponent::GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const
{
	if(CharacterCarriedWeaponMap.Contains(InWeaponTagToGet))
	{
		if(APuraBaseWeapon* const* FoundWeapon = CharacterCarriedWeaponMap.Find(InWeaponTagToGet))
		{
			return *FoundWeapon;
		}
	}
	return nullptr;
}

APuraBaseWeapon* UPawnCombatComponent::GetCharacterCurrentEquippedWeapon() const
{
	if(!CurrentEquippedWeaponTag.IsValid())
	{
		return nullptr;
	}
	return GetCharacterCarriedWeaponByTag(CurrentEquippedWeaponTag);
}

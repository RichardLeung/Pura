// Fill out your copyright notice in the Description page of Project Settings.


#include "PawnCombatComponent.h"

#include "Components/BoxComponent.h"
#include "Pura/Item/Weapon/PuraBaseWeapon.h"
#include "Pura/Util/PuraDebugHelper.h"


void UPawnCombatComponent::RegisterSpawnedWeapon(FGameplayTag InWeaponTagToRegister,
                                                 APuraBaseWeapon* InWeaponToRegister, bool bRegisterAsEquippedWeapon)
{
	checkf(!CharacterCarriedWeaponMap.Contains(InWeaponTagToRegister), TEXT("%s has already been added"), *InWeaponToRegister->GetName());
	check(InWeaponToRegister);
	CharacterCarriedWeaponMap.Emplace(InWeaponTagToRegister, InWeaponToRegister);
	InWeaponToRegister->OnWeaponHitTarget.BindUObject(this, &ThisClass::OnWeaponHitTargetActor);
	InWeaponToRegister->OnWeaponPullFromTarget.BindUObject(this, &ThisClass::OnWeaponPullFromTargetActor);
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

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType)
{
	if(ToggleDamageType == EToggleDamageType::CurrentEquippedWeapon)
    {
        if(APuraBaseWeapon* WeaponToToggle = GetCharacterCurrentEquippedWeapon())
        {
        	if(bShouldEnable)
        	{
        		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
        	}else
        	{
        		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        	}
        }
    }
    // else
    // {
    //     APuraBaseWeapon* WeaponToToggle = nullptr;
    //     switch(ToggleDamageType)
    //     {
    //     case EToggleDamageType::LeftHand:
    //         WeaponToToggle = GetCharacterCarriedWeaponByTag(FGameplayTag::RequestGameplayTag(FName("Weapon.LeftHand")));
    //         break;
    //     case EToggleDamageType::RightHand:
    //         WeaponToToggle = GetCharacterCarriedWeaponByTag(FGameplayTag::RequestGameplayTag(FName("Weapon.RightHand")));
    //         break;
    //     default:
    //         break;
    //     }
    //     if(WeaponToToggle)
    //     {
    //         	if(bShouldEnable)
    //         	{
    //         		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);	
    //         	}else
    //         	{
    //         		WeaponToToggle->GetWeaponCollisionBox()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    //         	}
    //     }
    // }
}

void UPawnCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
	
}

void UPawnCombatComponent::OnWeaponPullFromTargetActor(AActor* InteractedActor)
{
	
}

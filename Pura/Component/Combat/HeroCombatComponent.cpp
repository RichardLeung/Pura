// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Pura/Item/Weapon/PuraHeroWeapon.h"
#include "Pura/Util/PuraDebugHelper.h"
#include "Pura/Util/PuraGameplayTags.h"

APuraHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APuraHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

APuraHeroWeapon* UHeroCombatComponent::GetHeroCurrentEquippedWeapon() const
{
	return Cast<APuraHeroWeapon>(GetCharacterCurrentEquippedWeapon());
}

float UHeroCombatComponent::GetHeroCurrentEquippedWeaponDamageAtLevel(float InLevel) const
{
	return Cast<APuraHeroWeapon>(GetCharacterCurrentEquippedWeapon())->HeroWeaponData.WeaponBaseDamage.GetValueAtLevel(InLevel);
}

void UHeroCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
	if (OverloppedActors.Contains(HitActor))
	{
		return;
	}
	OverloppedActors.AddUnique(HitActor);
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = HitActor;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		GetOwningPawn(),
		PuraGameplayTags::Shared_Event_MeleeHit,
		Data
	);
	
}

void UHeroCombatComponent::OnWeaponPullFromTargetActor(AActor* InteractedActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + " weapon pulled from " + InteractedActor->GetActorNameOrLabel(), FColor::Red);
}

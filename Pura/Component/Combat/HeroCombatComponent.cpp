// Fill out your copyright notice in the Description page of Project Settings.


#include "HeroCombatComponent.h"
#include "Pura/Item/Weapon/PuraHeroWeapon.h"
#include "Pura/Util/PuraDebugHelper.h"

APuraHeroWeapon* UHeroCombatComponent::GetHeroCarriedWeaponByTag(FGameplayTag InWeaponTag) const
{
	return Cast<APuraHeroWeapon>(GetCharacterCarriedWeaponByTag(InWeaponTag));
}

void UHeroCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + " hit " + HitActor->GetActorNameOrLabel(), FColor::Green);
}

void UHeroCombatComponent::OnWeaponPullFromTargetActor(AActor* InteractedActor)
{
	Debug::Print(GetOwningPawn()->GetActorNameOrLabel() + " weapon pulled from " + InteractedActor->GetActorNameOrLabel(), FColor::Red);
}

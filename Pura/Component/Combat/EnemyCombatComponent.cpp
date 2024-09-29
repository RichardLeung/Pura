// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Pura/Util/PuraDebugHelper.h"
#include "Pura/Util/PuraFunctionLibrary.h"
#include "Pura/Util/PuraGameplayTags.h"

void UEnemyCombatComponent::OnWeaponHitTargetActor(AActor* HitActor)
{
	if(OverloppedActors.Contains(HitActor))
	{
		return;
	}
	OverloppedActors.AddUnique(HitActor);
	// TODO: Implement block check
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UPuraFunctionLibrary::NativeDoesActorHaveTag(HitActor, PuraGameplayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnblockable = UPuraFunctionLibrary::NativeDoesActorHaveTag(GetOwningPawn(), PuraGameplayTags::Enemy_Status_Unblockable);
	if(bIsPlayerBlocking && !bIsMyAttackUnblockable)
	{
		// TODO: check if the block is valid
		bIsValidBlock = UPuraFunctionLibrary::IsValidBlock(GetOwningPawn(),HitActor);
	}
	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	if(bIsValidBlock)
	{
		// TODO: Implement block logic
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			PuraGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}else
	{
		// TODO: Implement hit logic
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			PuraGameplayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

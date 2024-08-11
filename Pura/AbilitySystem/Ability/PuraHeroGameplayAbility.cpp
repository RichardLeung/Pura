// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraHeroGameplayAbility.h"
#include "Pura/Character/PuraHeroCharacter.h"
#include "Pura/Controller/PuraHeroController.h"

APuraHeroCharacter* UPuraHeroGameplayAbility::GetHeroCharacterFromActorInfo()
{
	if(!CachedPuraHeroCharacter.IsValid())
	{
		CachedPuraHeroCharacter = Cast<APuraHeroCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedPuraHeroCharacter.IsValid() ? CachedPuraHeroCharacter.Get() : nullptr;
}

APuraHeroController* UPuraHeroGameplayAbility::GetHeroControllerFromActorInfo()
{
	if(!CachedPuraHeroController.IsValid())
	{
		CachedPuraHeroController = Cast<APuraHeroController>(CurrentActorInfo->PlayerController);
	}
	return CachedPuraHeroController.IsValid() ? CachedPuraHeroController.Get() : nullptr;
}

UHeroCombatComponent* UPuraHeroGameplayAbility::GetHeroCombatComponentFromActorInfo()
{
	return GetHeroCharacterFromActorInfo()->GetHeroCombatComponent();
}

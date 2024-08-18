// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraEnemyGameplayAbility.h"
#include "Pura/Character/PuraEnemyCharacter.h"

APuraEnemyCharacter* UPuraEnemyGameplayAbility::GetEnemyCharacterFromActorInfo()
{
	if(!CachedPuraEnemyCharacter.IsValid())
	{
		CachedPuraEnemyCharacter = Cast<APuraEnemyCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedPuraEnemyCharacter.IsValid() ? CachedPuraEnemyCharacter.Get() : nullptr;
}

UEnemyCombatComponent* UPuraEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

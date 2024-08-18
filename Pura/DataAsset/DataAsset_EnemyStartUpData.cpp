﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset_EnemyStartUpData.h"
#include "Pura/AbilitySystem/Ability/PuraEnemyGameplayAbility.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"

void UDataAsset_EnemyStartUpData::GiveToAbilitySystemComponent(UPuraAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
	if(!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UPuraEnemyGameplayAbility>& AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;
			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;
			InASCToGive->GiveAbility(AbilitySpec);
		}
		
	}
}
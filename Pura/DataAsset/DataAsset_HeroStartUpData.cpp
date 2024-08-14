// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset_HeroStartUpData.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/AbilitySystem/Ability/PuraGameplayAbility.h"

void UDataAsset_HeroStartUpData::GiveToAbilitySystemComponent(UPuraAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	for (const FPuraHeroAbilitySet& AbilitySet : HeroStartUpAbilitySets)
	{
		if (!AbilitySet.IsValid()) continue;

		FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);
		InASCToGive->GiveAbility(AbilitySpec);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset_StartUpBase.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/AbilitySystem/Ability/PuraGameplayAbility.h"

void UDataAsset_StartUpBase::GiveToAbilitySystemComponent(UPuraAbilitySystemComponent* InASCToGive,
                                                           int32 ApplyLevel)
{
	check(InASCToGive);
	GrantAbilities(ActivateOnGivenAbilities, InASCToGive, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASCToGive, ApplyLevel);
}

void UDataAsset_StartUpBase::GrantAbilities(
	const TArray<TSubclassOf<UPuraGameplayAbility>>& InAbilitiesToGive,
	UPuraAbilitySystemComponent* InASCToGive,
	int32 ApplyLevel)
{
	if(InAbilitiesToGive.IsEmpty())
	{
		return;
	}
	for(const TSubclassOf<UPuraGameplayAbility>& Ability : InAbilitiesToGive)
	{
		if(!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		InASCToGive->GiveAbility(AbilitySpec);
	}
}

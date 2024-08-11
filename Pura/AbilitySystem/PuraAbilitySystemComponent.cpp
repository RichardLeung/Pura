﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraAbilitySystemComponent.h"


void UPuraAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid()) return;
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if(!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UPuraAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	if(!InInputTag.IsValid()) return;
}

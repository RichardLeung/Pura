﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraStructTypes.h"
#include "Pura/AbilitySystem/Ability/PuraHeroGameplayAbility.h"

bool FPuraHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}

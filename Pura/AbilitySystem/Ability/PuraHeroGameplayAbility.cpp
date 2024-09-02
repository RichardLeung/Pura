// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraHeroGameplayAbility.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/Character/PuraHeroCharacter.h"
#include "Pura/Controller/PuraHeroController.h"
#include "Pura/Util/PuraGameplayTags.h"

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

FGameplayEffectSpecHandle UPuraHeroGameplayAbility::MakeHeroDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> InEffectClass, float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag,
	int32 InUsingComboCount)
{
	check(InEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetPuraAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	FGameplayEffectSpecHandle EffectSpecHandle = GetPuraAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		InEffectClass,
		GetAbilityLevel(),
		ContextHandle
		);
	
	if(InCurrentAttackTypeTag.IsValid())
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(
		InCurrentAttackTypeTag,
		InUsingComboCount
	);
	}else
	{
		EffectSpecHandle.Data->SetSetByCallerMagnitude(
		PuraGameplayTags::Shared_SetByCaller_BaseDamage,
		InWeaponBaseDamage
	);
	}
	return EffectSpecHandle;
}

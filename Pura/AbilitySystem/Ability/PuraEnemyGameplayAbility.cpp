// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraEnemyGameplayAbility.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/Character/PuraEnemyCharacter.h"
#include "Pura/Util/PuraGameplayTags.h"

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

FGameplayEffectSpecHandle UPuraEnemyGameplayAbility::MakeEnemyDamageEffectSpecHandle(
	TSubclassOf<UGameplayEffect> InEffectClass, const FScalableFloat& InDamageScalableFloat)
{
	check(InEffectClass);
	FGameplayEffectContextHandle ContextHandle = GetPuraAbilitySystemComponentFromActorInfo()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
	FGameplayEffectSpecHandle EffectSpecHandle = GetPuraAbilitySystemComponentFromActorInfo()->MakeOutgoingSpec(
		InEffectClass,
		GetAbilityLevel(),
		ContextHandle);
	EffectSpecHandle.Data->SetSetByCallerMagnitude(
		PuraGameplayTags::Shared_SetByCaller_BaseDamage,
		InDamageScalableFloat.GetValueAtLevel(GetAbilityLevel()));
	return EffectSpecHandle;
}

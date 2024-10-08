// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraGameplayAbility.h"
#include "PuraHeroGameplayAbility.generated.h"

class UHeroUIComponent;
class UHeroCombatComponent;
class APuraHeroController;
class APuraHeroCharacter;
/**
 * 
 */
UCLASS()
class PURA_API UPuraHeroGameplayAbility : public UPuraGameplayAbility
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category="Pura|Ability")
	APuraHeroCharacter* GetHeroCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Pura|Ability")
	APuraHeroController* GetHeroControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Pura|Ability")
	UHeroCombatComponent* GetHeroCombatComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Pura|Ability")
	UHeroUIComponent* GetHeroUIComponentFromActorInfo();

	UFUNCTION(BlueprintPure, Category="Pura|Ability")
	FGameplayEffectSpecHandle MakeHeroDamageEffectSpecHandle(
		TSubclassOf<UGameplayEffect> InEffectClass,
		float InWeaponBaseDamage,
		FGameplayTag InCurrentAttackTypeTag,
		int32 InUsingComboCount
		);

	UFUNCTION(BlueprintCallable, Category="Pura|Ability")
	bool GetAbilityRemainingCooldownByTag(FGameplayTag InAbilityCooldownTag, float& OutTotalCooldownTime, float& OutRemainingCooldownTime);
	
private:
	TWeakObjectPtr<APuraHeroCharacter> CachedPuraHeroCharacter;
	TWeakObjectPtr<APuraHeroController> CachedPuraHeroController;
};

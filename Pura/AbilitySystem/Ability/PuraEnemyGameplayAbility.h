// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraGameplayAbility.h"
#include "PuraEnemyGameplayAbility.generated.h"

class APuraEnemyCharacter;
class UEnemyCombatComponent;

/**
 * 
 */
UCLASS()
class PURA_API UPuraEnemyGameplayAbility : public UPuraGameplayAbility
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category = "Pura|Ability")
	APuraEnemyCharacter* GetEnemyCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Pura|Ability")
	UEnemyCombatComponent* GetEnemyCombatComponentFromActorInfo();
	
	UFUNCTION(BlueprintPure, Category = "Pura|Ability")
	FGameplayEffectSpecHandle MakeEnemyDamageEffectSpecHandle(
		TSubclassOf<UGameplayEffect> InEffectClass,
		const FScalableFloat& InDamageScalableFloat);

private:
	TWeakObjectPtr<APuraEnemyCharacter> CachedPuraEnemyCharacter;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "Pura/Util/PuraEnumType.h"
#include "PuraGameplayAbility.generated.h"

class UPuraAbilitySystemComponent;
class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EPuraAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class PURA_API UPuraGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	virtual void OnGiveAbility(
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilitySpec& Spec) override;

	virtual void EndAbility(
		const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility,
		bool bWasCancelled) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PuraAbility")
	EPuraAbilityActivationPolicy AbilityActivationPolicy = EPuraAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category="Pura|Ability")
	UPawnCombatComponent* GetPawnCombatComponentFromActorInfo() const;

	UFUNCTION(BlueprintPure, Category="Pura|Ability")
	UPuraAbilitySystemComponent* GetPuraAbilitySystemComponentFromActorInfo() const;

	FActiveGameplayEffectHandle NativeApplyEffectSpecHandleToTarget(AActor* TargetActor,const FGameplayEffectSpecHandle& InSpecHandle) const;

	UFUNCTION(BlueprintCallable, Category="Pura|Ability", meta=(DisplayName="Apply Gameplay Effect Spec Handle To Target Actor", ExpandEnumAsExecs="OutSuccessType"))
	FActiveGameplayEffectHandle BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle, EPuraSuccessType& OutSuccessType);
};

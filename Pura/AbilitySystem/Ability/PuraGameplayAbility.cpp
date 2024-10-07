// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/Component/Combat/PawnCombatComponent.h"
#include "Pura/Util/PuraFunctionLibrary.h"
#include "Pura/Util/PuraEnumType.h"
#include "Pura/Util/PuraGameplayTags.h"

void UPuraGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);
	if(AbilityActivationPolicy == EPuraAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo && !Spec.IsActive())
		{
			ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
		}
	}
}

void UPuraGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
                                      const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                      bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	if(AbilityActivationPolicy == EPuraAbilityActivationPolicy::OnGiven)
	{
		if(ActorInfo)
		{
			ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
		}
	}
}

UPawnCombatComponent* UPuraGameplayAbility::GetPawnCombatComponentFromActorInfo() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UPuraAbilitySystemComponent* UPuraGameplayAbility::GetPuraAbilitySystemComponentFromActorInfo() const
{
	return Cast<UPuraAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UPuraGameplayAbility::NativeApplyEffectSpecHandleToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& InSpecHandle) const
{
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	
	check(TargetActor && InSpecHandle.IsValid());

	return GetPuraAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(
		*InSpecHandle.Data,
		TargetASC
	);
}

FActiveGameplayEffectHandle UPuraGameplayAbility::BP_ApplyEffectSpecHandleToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& InSpecHandle, EPuraSuccessType& OutSuccessType)
{
	FActiveGameplayEffectHandle ActiveGEHandle = NativeApplyEffectSpecHandleToTarget(TargetActor, InSpecHandle);
	OutSuccessType = ActiveGEHandle.WasSuccessfullyApplied() ? EPuraSuccessType::Success : EPuraSuccessType::Failure;
	return ActiveGEHandle;
}

void UPuraGameplayAbility::ApplyGameplayEffectSpecHandleToHitResults(const FGameplayEffectSpecHandle& InSpecHandle,
	const TArray<FHitResult>& InHitResults)
{
	if (InHitResults.IsEmpty())
	{
		return;
	}
	APawn* OwningPawn = CastChecked<APawn>(GetAvatarActorFromActorInfo());
	for (const FHitResult& HitResult : InHitResults)
	{
		if (APawn* HitPawn = Cast<APawn>(HitResult.GetActor()))
		{
			if (UPuraFunctionLibrary::IsTargetPawnHostile(OwningPawn, HitPawn))
			{
				FActiveGameplayEffectHandle ActiveGEHandle = NativeApplyEffectSpecHandleToTarget(HitPawn, InSpecHandle);
				if (ActiveGEHandle.WasSuccessfullyApplied())
				{
					FGameplayEventData EventData;
					EventData.Target = HitPawn;
					EventData.Instigator = OwningPawn;
					UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
						HitPawn,
						PuraGameplayTags::Shared_Event_HitReact,
						EventData
						);
				}
			}
		}
	}
}


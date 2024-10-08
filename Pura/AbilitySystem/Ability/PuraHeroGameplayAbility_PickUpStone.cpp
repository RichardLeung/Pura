// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraHeroGameplayAbility_PickUpStone.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Pura/Character/PuraHeroCharacter.h"
#include "Pura/Component/UI/HeroUIComponent.h"
#include "Pura/Item/PickUp/PuraStoneBase.h"

void UPuraHeroGameplayAbility_PickUpStone::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                           const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                           const FGameplayEventData* TriggerEventData)
{
	GetHeroUIComponentFromActorInfo()->OnStoneInteraction.Broadcast(true);
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
}

void UPuraHeroGameplayAbility_PickUpStone::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	GetHeroUIComponentFromActorInfo()->OnStoneInteraction.Broadcast(false);
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPuraHeroGameplayAbility_PickUpStone::CollectStone()
{
	CollectedStones.Empty();
	TArray<FHitResult> OutHits;
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetHeroCharacterFromActorInfo(),
		GetHeroCharacterFromActorInfo()->GetActorLocation(),
		GetHeroCharacterFromActorInfo()->GetActorLocation() + -GetHeroCharacterFromActorInfo()->GetActorUpVector() * BoxTraceDistance,
		BoxTraceSize/2.f,
		(-GetHeroCharacterFromActorInfo()->GetActorUpVector()).ToOrientationRotator(),
		StoneTraceChannel,
		false,
		TArray<AActor*>(),
		bDrawDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		OutHits,
		true
	);

	for (const FHitResult& Hit : OutHits)
	{
		if (APuraStoneBase* FoundStone = Cast<APuraStoneBase>(Hit.GetActor()))
		{
			CollectedStones.AddUnique(FoundStone);
		}
	}
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
	}
}

void UPuraHeroGameplayAbility_PickUpStone::ConsumeStone()
{
	if (CollectedStones.IsEmpty())
	{
		CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
		return;
	}
	for (APuraStoneBase* CollectedStone : CollectedStones)
	{
		CollectedStone->Consume(GetHeroCharacterFromActorInfo()->GetPuraAbilitySystemComponent(), GetAbilityLevel());
	}
}

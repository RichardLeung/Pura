// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraStoneBase.h"

#include "Components/SphereComponent.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/Character/PuraHeroCharacter.h"
#include "Pura/Util/PuraGameplayTags.h"


void APuraStoneBase::Consume(UPuraAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel)
{
	check(StoneGameplayEffectClass);

	UGameplayEffect* EffectCDO = StoneGameplayEffectClass->GetDefaultObject<UGameplayEffect>();
	
	AbilitySystemComponent->ApplyGameplayEffectToSelf(EffectCDO, ApplyLevel, AbilitySystemComponent->MakeEffectContext());
	
	BP_OnStoneConsumed();
}

void APuraStoneBase::OnPickUpCollisionSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(APuraHeroCharacter* OverlappedHeroCharacter = Cast<APuraHeroCharacter>(OtherActor))
	{
		OverlappedHeroCharacter->GetPuraAbilitySystemComponent()->TryActivateAbilityByTag(PuraGameplayTags::Player_Ability_PickUp_Stone);
	}
	
}

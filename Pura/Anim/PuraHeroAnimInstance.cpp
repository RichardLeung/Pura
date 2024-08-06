// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraHeroAnimInstance.h"
#include "Pura/Character/PuraHeroCharacter.h"

void UPuraHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (OwningCharacter)
	{
		OwningHeroCharacter = Cast<APuraHeroCharacter>(OwningCharacter);
	}
}

void UPuraHeroAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);
	if (bHasAcceleration)
	{
		IdleElapsedTime = 0.f;
		bShouldEnterRelaxState = false;
	}else
	{
		IdleElapsedTime += DeltaSeconds;
		bShouldEnterRelaxState = IdleElapsedTime >= EnterRelaxStateThreshold;
	}
}

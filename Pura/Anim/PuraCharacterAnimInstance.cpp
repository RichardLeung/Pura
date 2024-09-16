// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraCharacterAnimInstance.h"

#include "KismetAnimationLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pura/Character/PuraBaseCharacter.h"

void UPuraCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<APuraBaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningCharacterMovement = OwningCharacter->GetCharacterMovement();
	}
}

void UPuraCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if(!OwningCharacter || !OwningCharacterMovement)
	{
		return;
	}
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();
	bHasAcceleration = OwningCharacterMovement->GetCurrentAcceleration().Size2D() > 0.0f;

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(OwningCharacter->GetVelocity(), OwningCharacter->GetActorRotation());
}



// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraBaseAnimInstance.h"
#include "PuraCharacterAnimInstance.generated.h"

class UCharacterMovementComponent;
class APuraBaseCharacter;

/**
 * 
 */
UCLASS()
class PURA_API UPuraCharacterAnimInstance : public UPuraBaseAnimInstance
{
	GENERATED_BODY()
public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;

protected:
	UPROPERTY()
	APuraBaseCharacter* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningCharacterMovement;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float LocomotionDirection;
};

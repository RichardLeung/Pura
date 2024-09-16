// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagContainer.h"
#include "PuraBaseAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PURA_API UPuraBaseAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe), Category = "AnimData|LocomotionData")
	bool DoesOwnerHaveTag(FGameplayTag TagToCheck) const;
};

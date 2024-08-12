// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraBaseAnimInstance.h"
#include "PuraHeroLinkedAnimLayer.generated.h"

class UPuraHeroAnimInstance;

/**
 * 
 */
UCLASS()
class PURA_API UPuraHeroLinkedAnimLayer : public UPuraBaseAnimInstance
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, meta=(BlueprintThreadSafe))
	UPuraHeroAnimInstance* GetHeroAnimInstance() const;
	
};

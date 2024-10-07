// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraPickUpBase.h"
#include "PuraStoneBase.generated.h"


class UGameplayEffect;
class UPuraAbilitySystemComponent;

UCLASS()
class PURA_API APuraStoneBase : public APuraPickUpBase
{
	GENERATED_BODY()

public:
	void Consume(UPuraAbilitySystemComponent* AbilitySystemComponent, int32 ApplyLevel);
	
protected:
	virtual void OnPickUpCollisionSphereBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult
		) override;

	UFUNCTION(BlueprintImplementableEvent, meta=(DisplayName = "On Stone Consumed"))
	void BP_OnStoneConsumed();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> StoneGameplayEffectClass;
};

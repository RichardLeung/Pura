// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnCombatComponent.h"
#include "EnemyCombatComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PURA_API UEnemyCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()

public:
	virtual void OnWeaponHitTargetActor(AActor* HitActor) override;

	UFUNCTION(BlueprintCallable, Category="Pura|Combat")
	APawn* GetCombatTarget();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pura|Combat")
	APawn* CombatTarget;

	virtual void ToggleBodyPartCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType) override;
};

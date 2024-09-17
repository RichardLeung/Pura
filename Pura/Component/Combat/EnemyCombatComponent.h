﻿// Fill out your copyright notice in the Description page of Project Settings.

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
	
};

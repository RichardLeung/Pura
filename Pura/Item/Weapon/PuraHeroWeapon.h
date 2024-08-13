// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraBaseWeapon.h"
#include "Pura/Util/PuraStructTypes.h"
#include "PuraHeroWeapon.generated.h"

UCLASS()
class PURA_API APuraHeroWeapon : public APuraBaseWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="WeaponData")
	FPuraHeroWeaponData HeroWeaponData;
};
	
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PuraStructTypes.generated.h"

class UPuraHeroLinkedAnimLayer;

USTRUCT(BlueprintType)
struct FPuraHeroWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPuraHeroLinkedAnimLayer> WeaponAnimLayerToLink;
};
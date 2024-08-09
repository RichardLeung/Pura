// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Pura/Component/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"


class APuraBaseWeapon;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PURA_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category="Pura|Combat")
	void RegisterSpawnedWeapon(
		FGameplayTag InWeaponTagToRegister,
		APuraBaseWeapon* InWeaponToRegister,
		bool bRegisterAsEquippedWeapon);

	UFUNCTION(BlueprintCallable, Category="Pura|Combat")
	APuraBaseWeapon* GetCharacterCarriedWeaponByTag(FGameplayTag InWeaponTagToGet) const;

	UPROPERTY(BlueprintReadWrite, Category="Pura|Combat")
	FGameplayTag CurrentEquippedWeaponTag;
	
	UFUNCTION(BlueprintCallable, Category="Pura|Combat")
	APuraBaseWeapon* GetCharacterCurrentEquippedWeapon() const;
private:
	TMap<FGameplayTag, APuraBaseWeapon*> CharacterCarriedWeaponMap;
};

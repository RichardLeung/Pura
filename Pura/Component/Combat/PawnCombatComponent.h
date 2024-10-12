// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Pura/Component/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

UENUM(BlueprintType)
enum EToggleDamageType: uint8
{
	CurrentEquippedWeapon,
	LeftHand,
	RightHand,
};


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

	UFUNCTION(BlueprintCallable, Category="Pura|Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType = EToggleDamageType::CurrentEquippedWeapon);

	UFUNCTION(BlueprintCallable, Category="Pura|Combat")
	void ToggleCharacterInvincible(bool bShouldEnable);
	
	virtual void OnWeaponHitTargetActor(AActor* HitActor);
	virtual void OnWeaponPullFromTargetActor(AActor* InteractedActor);

protected:
	virtual void ToggleCurrentEquippedWeaponCollision(bool bShouldEnable);

	virtual void ToggleBodyPartCollision(bool bShouldEnable, EToggleDamageType ToggleDamageType);
	
protected:
	TArray<AActor*> OverloppedActors;
	
private:
	TMap<FGameplayTag, APuraBaseWeapon*> CharacterCarriedWeaponMap;
};

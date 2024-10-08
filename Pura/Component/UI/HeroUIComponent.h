// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "PawnUIComponent.h"
#include "Pura/Util/PuraDebugHelper.h"
#include "HeroUIComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEquippedWeaponChangedDelegate, TSoftObjectPtr<UTexture2D>, SoftWeaponIcon);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAbilityIconSlotUpdatedDelegate, FGameplayTag, AbilityInputTag, TSoftObjectPtr<UMaterialInterface>, SoftAbilityIconMaterial);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAbilityCooldownBeginDelegate, FGameplayTag, AbilityInputTag, float, TotalCooldownTime, float, RemainingCooldownTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStoneInteractionDelegate, bool, bShouldDisplayInputkey);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PURA_API UHeroUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChangedDelegate OnCurrentRageChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnEquippedWeaponChangedDelegate OnEquippedWeaponChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAbilityIconSlotUpdatedDelegate OnAbilityIconSlotUpdated;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAbilityCooldownBeginDelegate OnAbilityCooldownBegin;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnStoneInteractionDelegate OnStoneInteraction;
};

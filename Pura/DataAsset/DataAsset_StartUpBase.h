// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpBase.generated.h"

class UPuraAbilitySystemComponent;
class UPuraGameplayAbility;
/**
 * 
 */
UCLASS()
class PURA_API UDataAsset_StartUpBase : public UDataAsset
{
	GENERATED_BODY()
public:
	 virtual void GiveToAbilitySystemComponent(
	 	UPuraAbilitySystemComponent* InASCToGive,
	 	int32 ApplyLevel = 1
	 	);
	
protected:
	UPROPERTY(EditDefaultsOnly, Category=StartUpData)
	TArray<TSubclassOf<UPuraGameplayAbility>> ActivateOnGivenAbilities;

	UPROPERTY(EditDefaultsOnly, Category=StartUpData)
	TArray<TSubclassOf<UPuraGameplayAbility>> ReactiveAbilities;

	void GrantAbilities(
		const TArray<TSubclassOf<UPuraGameplayAbility>>& InAbilitiesToGive,
		UPuraAbilitySystemComponent* InASCToGive,
		int32 ApplyLevel = 1
		);
};

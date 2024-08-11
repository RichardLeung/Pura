// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartUpBase.h"
#include "GameplayTagContainer.h"
#include "DataAsset_HeroStartUpData.generated.h"

USTRUCT(BlueprintType)
struct FPuraHeroAbilitySet
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UPuraGameplayAbility> AbilityToGrant;

	bool IsValid() const;
};

/**
 * 
 */
UCLASS()
class PURA_API UDataAsset_HeroStartUpData : public UDataAsset_StartUpBase
{
	GENERATED_BODY()

	virtual void GiveToAbilitySystemComponent(
		 UPuraAbilitySystemComponent* InASCToGive,
		 int32 ApplyLevel = 1
		 ) override;

private:
	UPROPERTY(EditDefaultsOnly, Category=StartUpData, meta=(TitleProperty="InputTag"))
	TArray<FPuraHeroAbilitySet> HeroStartUpAbilitySets;
};

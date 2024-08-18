// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset_StartUpBase.h"
#include "DataAsset_EnemyStartUpData.generated.h"

class UPuraEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class PURA_API UDataAsset_EnemyStartUpData : public UDataAsset_StartUpBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UPuraAbilitySystemComponent* InASCToGive, int32 ApplyLevel) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UPuraEnemyGameplayAbility>> EnemyCombatAbilities;
};

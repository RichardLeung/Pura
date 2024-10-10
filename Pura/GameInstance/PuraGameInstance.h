// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "PuraGameInstance.generated.h"


USTRUCT(BlueprintType)
struct FPuraGameLevelSet
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, meta = (Categories = "GameData.Level"))
	FGameplayTag LevelTag;
	
	UPROPERTY(EditDefaultsOnly)
	// TSoftObjectPtr<UWorld> Level;
	TSoftObjectPtr<UWorld> Level;

	bool IsValid() const
	{
		return LevelTag.IsValid() && !Level.IsNull();
	}
};

/**
 * 
 */
UCLASS()
class PURA_API UPuraGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FPuraGameLevelSet> GameLevelSets;

public:
	UFUNCTION(BlueprintPure, meta = (GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(const FGameplayTag InLevelTag) const;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "Pura/Util/PuraStructTypes.h"
#include "PuraGameInstance.generated.h"

class UPuraSaveGame;
class UDataTable;

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

public:
	virtual void Init() override;

protected:
	virtual void OnPreLoadMap(const FString& InMapName);

	virtual void OnDestinationWorld(UWorld* InLoadedWorld);

	void LoadDataTable();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FPuraGameLevelSet> GameLevelSets;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "存储数据")
	UPuraSaveGame* CurrentSaveGame;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "基础数据")
	TObjectPtr<UDataTable> DT_LevelExp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "基础数据")
	TArray<FPuraLevelExpRow> LevelExpData;

	UFUNCTION(BlueprintPure, meta = (GameplayTagFilter = "GameData.Level"))
	TSoftObjectPtr<UWorld> GetGameLevelByTag(const FGameplayTag InLevelTag) const;
};

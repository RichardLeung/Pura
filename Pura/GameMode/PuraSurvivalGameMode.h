// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraBaseGameMode.h"
#include "PuraSurvivalGameMode.generated.h"

class APuraEnemyCharacter;

UENUM(BlueprintType)
enum class EPuraSurvivalGameModeState: uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveCompleted,
	AllWavesDone,
	PlayerDied
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSurvivalGameModeStateChangedDelegate, EPuraSurvivalGameModeState, CurrentState);

USTRUCT(BlueprintType)
struct FPuraEnemyWaveSpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<APuraEnemyCharacter> SoftEnemyClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 MinPerSpawnCount = 1;

	UPROPERTY(EditAnywhere)
	int32 MaxPerSpawnCount = 3;
};

USTRUCT(BlueprintType)
struct FPuraEnemyWaveSpawnerTableRow: public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FPuraEnemyWaveSpawnerInfo> EnemyWaveSpawnerInfos;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemyToSpanThisWave = 1;
};

/**
 * 
 */
UCLASS()
class PURA_API APuraSurvivalGameMode : public APuraBaseGameMode
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:
	void SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState InState);

	bool HasFinishedAllWaves() const;
	
	UPROPERTY()
	EPuraSurvivalGameModeState CurrentSurvivalGameModeState;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSurvivalGameModeStateChangedDelegate OnSurvivalGameModeStateChanged;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Wave Spawner", meta = (AllowPrivateAccess = "true"))
	UDataTable* EnemyWaveSpawnerDataTable;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Enemy Wave Spawner", meta = (AllowPrivateAccess = "true"))
	int32 TotalWavesToSpawn;

	UPROPERTY()
	int32 CurrentWaveCount = 1;

	UPROPERTY()
	float TimePassedSinceStart = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Wave Spawner", meta = (AllowPrivateAccess = "true"))
	float SpawnNewWaveWaitTime = 5.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Wave Spawner", meta = (AllowPrivateAccess = "true"))
	float SpawnEnemyDelayTime = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enemy Wave Spawner", meta = (AllowPrivateAccess = "true"))
	float WaveCompletedWaitTime = 5.f;
};

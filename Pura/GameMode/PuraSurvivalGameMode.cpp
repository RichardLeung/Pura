// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraSurvivalGameMode.h"

#include "Engine/AssetManager.h"
#include "Pura/Character/PuraEnemyCharacter.h"

void APuraSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	checkf(EnemyWaveSpawnerDataTable, TEXT("EnemyWaveSpawnerDataTable is not set in %s. Please set it in the editor."), *GetName());
	SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState::WaitSpawnNewWave);
	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
	PreLoadNextWaveEnemies();
}

void APuraSurvivalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurrentSurvivalGameModeState == EPuraSurvivalGameModeState::WaitSpawnNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;
		if (TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			TimePassedSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState::SpawningNewWave);
		}
	}
	if (CurrentSurvivalGameModeState == EPuraSurvivalGameModeState::SpawningNewWave)
	{
		TimePassedSinceStart += DeltaSeconds;
		if (TimePassedSinceStart >= SpawnEnemyDelayTime)
		{
			// TODO: Handle Spawn New Enemy

			TimePassedSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState::InProgress);
		}
	}
	if (CurrentSurvivalGameModeState == EPuraSurvivalGameModeState::WaveCompleted)
	{
		TimePassedSinceStart += DeltaSeconds;
		if (TimePassedSinceStart >= WaveCompletedWaitTime)
		{
			TimePassedSinceStart = 0.f;
			CurrentWaveCount++;
			if (HasFinishedAllWaves())
			{
				SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState::AllWavesDone);
			}else
			{
				SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState::WaitSpawnNewWave);
				PreLoadNextWaveEnemies();
			}
		}
	}
}

void APuraSurvivalGameMode::SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState InState)
{
	CurrentSurvivalGameModeState = InState;
	OnSurvivalGameModeStateChanged.Broadcast(CurrentSurvivalGameModeState);
}

bool APuraSurvivalGameMode::HasFinishedAllWaves() const
{
	return CurrentWaveCount > TotalWavesToSpawn;
}

void APuraSurvivalGameMode::PreLoadNextWaveEnemies()
{
	if (HasFinishedAllWaves())
	{
		return;
	}

	for (const FPuraEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerInfos)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;
		UAssetManager::GetStreamableManager().RequestAsyncLoad(
			SpawnerInfo.SoftEnemyClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda([SpawnerInfo, this]()
			{
				if(UClass* LoadedEnemyClass = SpawnerInfo.SoftEnemyClassToSpawn.Get())
				{
					PreLoadedEnemyClassMap.Emplace(SpawnerInfo.SoftEnemyClassToSpawn, LoadedEnemyClass);
				}
			})
			);
	}
}

FPuraEnemyWaveSpawnerTableRow* APuraSurvivalGameMode::GetCurrentWaveSpawnerTableRow() const
{
	const FName RowName = FName(TEXT("Wave")+FString::FromInt(CurrentWaveCount));
	FPuraEnemyWaveSpawnerTableRow* FoundRow = EnemyWaveSpawnerDataTable->FindRow<FPuraEnemyWaveSpawnerTableRow>(RowName, TEXT(""));
	checkf(FoundRow, TEXT("Row %s not found in %s"), *RowName.ToString(), *EnemyWaveSpawnerDataTable->GetName());
	return FoundRow;
}

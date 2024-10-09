// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraSurvivalGameMode.h"

void APuraSurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();
	checkf(EnemyWaveSpawnerDataTable, TEXT("EnemyWaveSpawnerDataTable is not set in %s. Please set it in the editor."), *GetName());
	SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState::WaitSpawnNewWave);
	TotalWavesToSpawn = EnemyWaveSpawnerDataTable->GetRowNames().Num();
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
		if (TimePassedSinceStart >= SpawnNewWaveWaitTime)
		{
			// TODO: Handle Spawn New Enemy

			TimePassedSinceStart = 0.f;
			SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState::InProgress);
		}
	}
	if (CurrentSurvivalGameModeState == EPuraSurvivalGameModeState::InProgress)
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
	return CurrentWaveCount >= TotalWavesToSpawn;
}

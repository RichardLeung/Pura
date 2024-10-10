// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraSurvivalGameMode.h"

#include "NavigationSystem.h"
#include "Engine/AssetManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"
#include "Pura/Character/PuraEnemyCharacter.h"
#include "Pura/Util/PuraDebugHelper.h"

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
			CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
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
	PreLoadedEnemyClassMap.Empty();
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

int32 APuraSurvivalGameMode::TrySpawnWaveEnemies()
{
	if(TargetPoints.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), TargetPoints);
	}
	checkf(!TargetPoints.IsEmpty(), TEXT("No TargetPoints found in %s"), *GetWorld()->GetName());
	uint32 EnemiesSpawnedThisTime = 0;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	for (const FPuraEnemyWaveSpawnerInfo& SpawnerInfo : GetCurrentWaveSpawnerTableRow()->EnemyWaveSpawnerInfos)
	{
		if (SpawnerInfo.SoftEnemyClassToSpawn.IsNull()) continue;
		if (UClass** LoadedEnemyClass = PreLoadedEnemyClassMap.Find(SpawnerInfo.SoftEnemyClassToSpawn))
		{
			// 取最小到最大之间的随机数
			const int32 NumToSpawn = FMath::RandRange(SpawnerInfo.MinPerSpawnCount, SpawnerInfo.MaxPerSpawnCount);
			UClass* LoadedClass = PreLoadedEnemyClassMap.FindChecked(SpawnerInfo.SoftEnemyClassToSpawn);
			for (int32 i = 0; i < NumToSpawn; i++)
			{
				const int32 RandomTargetPointIndex = FMath::RandRange(0, TargetPoints.Num()-1);
				ATargetPoint* TargetPoint = Cast<ATargetPoint>(TargetPoints[RandomTargetPointIndex]);
				const FVector SpawnLocation = TargetPoint->GetActorLocation();
				const FRotator SpawnRotation = TargetPoint->GetActorForwardVector().ToOrientationRotator();
				FVector RandomLocation;
				UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnLocation, RandomLocation, 400.f);
				RandomLocation += FVector(0.f, 0.f, 150.f);
				APuraEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<APuraEnemyCharacter>(LoadedClass, RandomLocation, SpawnRotation);
				if(SpawnedEnemy)
				{
					SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
					EnemiesSpawnedThisTime++;
					TotalSpawnedEnemiesThisWaveCounter++;
				}
				if(!ShouldKeepSpawnEnemies())
				{
					return EnemiesSpawnedThisTime;
				}
			}
		}
	}
	
	return EnemiesSpawnedThisTime;
}

bool APuraSurvivalGameMode::ShouldKeepSpawnEnemies() const
{
	return TotalSpawnedEnemiesThisWaveCounter < GetCurrentWaveSpawnerTableRow()->TotalEnemyToSpanThisWave;
}

void APuraSurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	CurrentSpawnedEnemiesCounter--;
	if (ShouldKeepSpawnEnemies())
	{
		CurrentSpawnedEnemiesCounter += TrySpawnWaveEnemies();
	}else if (CurrentSpawnedEnemiesCounter == 0)
	{
		TotalSpawnedEnemiesThisWaveCounter = 0;
		CurrentSpawnedEnemiesCounter = 0;
		SetCurrentSurvivalGameModeState(EPuraSurvivalGameModeState::WaveCompleted);
	}
}

void APuraSurvivalGameMode::RegisterSpawnEnemies(const TArray<APuraEnemyCharacter*> InSpawnedEnemies)
{
	for (APuraEnemyCharacter* SpawnedEnemy : InSpawnedEnemies)
	{
		if (SpawnedEnemy)
		{
			CurrentSpawnedEnemiesCounter++;
			SpawnedEnemy->OnDestroyed.AddUniqueDynamic(this, &ThisClass::OnEnemyDestroyed);
		}
	}
}

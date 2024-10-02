// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilityTask_WaitSpawnEnemy.h"
#include "AbilitySystemComponent.h"
#include "NavigationSystem.h"
#include "Engine/AssetManager.h"
#include "Pura/Character/PuraEnemyCharacter.h"
#include "Pura/Util/PuraDebugHelper.h"

UAbilityTask_WaitSpawnEnemy* UAbilityTask_WaitSpawnEnemy::WaitSpawnEnemy(UGameplayAbility* OwningAbility,
                                                                         FGameplayTag EventTag, TSoftClassPtr<APuraEnemyCharacter> SoftEnemyClassToSpawn, int32 NumToSpawn,
                                                                         const FVector& SpawnOrigin, float RandomSpawnRadius)
{
	UAbilityTask_WaitSpawnEnemy* Node = NewAbilityTask<UAbilityTask_WaitSpawnEnemy>(OwningAbility);
	Node->CachedEventTag = EventTag;
	Node->CachedSoftEnemyClassToSpawn = SoftEnemyClassToSpawn;
	Node->CachedNumToSpawn = NumToSpawn;
	Node->CachedSpawnOrigin = SpawnOrigin;
	Node->CachedRandomSpawnRadius = RandomSpawnRadius;
	return Node;
}

void UAbilityTask_WaitSpawnEnemy::Activate()
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	DelegateHandle = Delegate.AddUObject(this, &UAbilityTask_WaitSpawnEnemy::OnGameplayEventReceived);
	
}

void UAbilityTask_WaitSpawnEnemy::OnDestroy(bool bInOwnerFinished)
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	Delegate.Remove(DelegateHandle);
	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_WaitSpawnEnemy::OnGameplayEventReceived(const FGameplayEventData* InPayload)
{
	if(ensure(!CachedSoftEnemyClassToSpawn.IsNull()))
	{
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(
		CachedSoftEnemyClassToSpawn.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(this, &ThisClass::OnEnemyClassLoaded));
	}else
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidnotSpawn.Broadcast(TArray<APuraEnemyCharacter*>());
		}
		EndTask();
	}
}

void UAbilityTask_WaitSpawnEnemy::OnEnemyClassLoaded()
{
	UClass* LoadedClass = CachedSoftEnemyClassToSpawn.Get();
	UWorld* World = GetWorld();
	if(!LoadedClass || !World)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidnotSpawn.Broadcast(TArray<APuraEnemyCharacter*>());
		}
		EndTask();
		return;
	}
	TArray<APuraEnemyCharacter*> SpawnedEnemies;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	for(int32 i = 0; i < CachedNumToSpawn; i++)
	{
		FVector RandomLocation;
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(
			this,
			CachedSpawnOrigin,
			RandomLocation,
			CachedRandomSpawnRadius);
		RandomLocation += FVector(0, 0, 150);

		const FRotator SpawnFacingRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();
		
		APuraEnemyCharacter* SpawnedEnemy = World->SpawnActor<APuraEnemyCharacter>(LoadedClass, RandomLocation, SpawnFacingRotation, SpawnParams);
		if(SpawnedEnemy)
		{
			SpawnedEnemies.Add(SpawnedEnemy);
		}
	}
	if (ShouldBroadcastAbilityTaskDelegates())
	{
		if(!SpawnedEnemies.IsEmpty())
		{
			OnSpawnFinished.Broadcast(SpawnedEnemies);
		}else
		{
			DidnotSpawn.Broadcast(TArray<APuraEnemyCharacter*>());
		}
	}
	
	EndTask();
}

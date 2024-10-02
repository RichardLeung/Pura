// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitSpawnEnemy.generated.h"

class APuraEnemyCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemyDelegate, const TArray<APuraEnemyCharacter*>&, SpawnedEnemies);

/**
 * 
 */
UCLASS()
class PURA_API UAbilityTask_WaitSpawnEnemy : public UAbilityTask
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable,
		Category="Pura|AbilityTask",
		meta = (
			DisplayName="Wait Gameplay Event And Spawn Enemies",
			HidePin = "OwningAbility",
			DefaultToSelf="OwningAbility",
			BlueprintInternalUseOnly = "true",
			NumToSpawn = "1",
			RandomSpawnRadius = "200"
			))
	static UAbilityTask_WaitSpawnEnemy* WaitSpawnEnemy(
		UGameplayAbility* OwningAbility,
		FGameplayTag EventTag,
		TSoftClassPtr<APuraEnemyCharacter> SoftEnemyClassToSpawn,
		int32 NumToSpawn,
		const FVector& SpawnOrigin,
		float RandomSpawnRadius);

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemyDelegate OnSpawnFinished;

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemyDelegate DidnotSpawn;

	//~ Begin UGameplayTask Interface
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	//~ End UGameplayTask Interface

private:
	FGameplayTag CachedEventTag;
	TSoftClassPtr<APuraEnemyCharacter> CachedSoftEnemyClassToSpawn;
	int32 CachedNumToSpawn;
	FVector CachedSpawnOrigin;
	float CachedRandomSpawnRadius;
	FDelegateHandle DelegateHandle;

	void OnGameplayEventReceived(const FGameplayEventData* InPayload);

	void OnEnemyClassLoaded();
};

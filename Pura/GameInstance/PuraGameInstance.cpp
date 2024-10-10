// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraGameInstance.h"

TSoftObjectPtr<UWorld> UPuraGameInstance::GetGameLevelByTag(const FGameplayTag InLevelTag) const 
{
	for (const FPuraGameLevelSet& LevelSet : GameLevelSets)
	{
		if (!LevelSet.IsValid()) continue;
		
		if (LevelSet.LevelTag == InLevelTag)
		{
			return LevelSet.Level;
		}
	}
	return TSoftObjectPtr<UWorld>();
}

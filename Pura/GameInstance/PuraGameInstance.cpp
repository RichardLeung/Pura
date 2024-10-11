// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraGameInstance.h"

#include "MoviePlayer.h"

void UPuraGameInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnDestinationWorld);
}

void UPuraGameInstance::OnPreLoadMap(const FString& InMapName)
{
	FLoadingScreenAttributes LoadingScreenAttributes;
	LoadingScreenAttributes.bAutoCompleteWhenLoadingCompletes = true;
	LoadingScreenAttributes.MinimumLoadingScreenDisplayTime = 2.f;
	LoadingScreenAttributes.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
	GetMoviePlayer()->SetupLoadingScreen(LoadingScreenAttributes);
}

void UPuraGameInstance::OnDestinationWorld(UWorld* InLoadedWorld)
{
	GetMoviePlayer()->StopMovie();
}

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

// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraGameInstance.h"
#include "MoviePlayer.h"
#include "Pura/Util/PuraDebugHelper.h"

void UPuraGameInstance::Init()
{
	Super::Init();
	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &ThisClass::OnPreLoadMap);
	FCoreUObjectDelegates::PostLoadMapWithWorld.AddUObject(this, &ThisClass::OnDestinationWorld);
	LoadDataTable();
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

void UPuraGameInstance::LoadDataTable()
{
	// Load DataTable
	// 加载升级经验数据表
	TArray<FName> AllLevelExpKeys = DT_LevelExp->GetRowNames();
	Debug::Print(TEXT("加载LevelExpDataTable,包含等级：" + FString::FromInt(AllLevelExpKeys.Num())));
	LevelExpData.Empty();
	// 获取UDataTable的RowMap，这是一个包含所有行的TMap，其中键为RowName，值为void指针
	const TMap<FName, uint8*>& Map_LevelExpDataTable = DT_LevelExp->GetRowMap();
	// 遍历RowMap并将每个行名和数据添加到我们的MyDataMap中
	for (const auto& RowPair_LevelExp : Map_LevelExpDataTable)
	{
		const FPuraLevelExpRow* RowData = reinterpret_cast<const FPuraLevelExpRow*>(
			RowPair_LevelExp.Value);
		LevelExpData.Add(*RowData);
	}
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

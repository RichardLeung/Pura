// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset_LevelUpInfo.h"

int32 UDataAsset_LevelUpInfo::FindLevelForEXP(int32 EXP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		if (LevelUpInfos.Num() - 1 <= Level)
		{
			return Level;
		}
		if (EXP >= LevelUpInfos[Level].LevelUpRequirement)
		{
			Level++;
		}
		else
		{
			bSearching = false;
		}
	}
	return Level;
}

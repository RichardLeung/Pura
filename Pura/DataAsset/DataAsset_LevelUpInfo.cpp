// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset_LevelUpInfo.h"

int32 UDataAsset_LevelUpInfo::FindLevelForEXP(int32 EXP) const
{
	int32 Level = 1;
	bool bSearching = true;
	while (bSearching)
	{
		// 索引【0】为空数据，所以需要减去1，索引下标表示对应等级的数据，如果遍历完成了整个数组，那么返回当前等级
		if (LevelUpInfos.Num() - 1 <= Level)
		{
			return Level;
		}
		// 如果当前经验值大于等于当前等级所需经验值，那么升级
		if (EXP >= LevelUpInfos[Level].LevelUpRequirement)
		{
			Level++;
		}
		else
		{
			// 如果经验值小于当前等级所需经验值，那么停止搜索
			bSearching = false;
		}
	}
	return Level;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::GetInputActionByTag(const FGameplayTag& Tag) const
{
	for (const FPuraInputActionConfig& ActionConfig : NativeInputActions)
	{
		if (ActionConfig.InputTag.MatchesTag(Tag)  && ActionConfig.InputAction)
		{
			return ActionConfig.InputAction;
		}
	}
	return nullptr;
}

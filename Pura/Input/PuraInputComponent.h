// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "Pura/DataAsset/DataAsset_InputConfig.h"
#include "PuraInputComponent.generated.h"


UCLASS()
class PURA_API UPuraInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserObject, typename CallbackFunc>
	void BindNativeInputAction(
		const UDataAsset_InputConfig* InInputConfig,
		const FGameplayTag& InInputTag,
		ETriggerEvent TriggerEvent,
		UserObject* ContextObject,
		CallbackFunc Func)
	{
		checkf(InInputConfig, TEXT("InputConfig is nullptr"));
		if (UInputAction* InputAction = InInputConfig->GetInputActionByTag(InInputTag))
		{
			BindAction(InputAction, TriggerEvent, ContextObject, Func);
		}
	}
};

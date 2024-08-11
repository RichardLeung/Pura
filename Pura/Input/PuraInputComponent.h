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
		CallbackFunc Func);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(
		const UDataAsset_InputConfig* InInputConfig,
		UserObject* ContextObject,
		CallbackFunc InputPressedFunc,
		CallbackFunc InputReleasedFunc);
};

template<class UserObject, typename CallbackFunc>
inline void UPuraInputComponent::BindNativeInputAction(
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

template <class UserObject, typename CallbackFunc>
void UPuraInputComponent::BindAbilityInputAction(
	const UDataAsset_InputConfig* InInputConfig,
	UserObject* ContextObject,
	CallbackFunc InputPressedFunc,
	CallbackFunc InputReleasedFunc)
{
	checkf(InInputConfig, TEXT("InputConfig is nullptr"));
	for (const FPuraInputActionConfig& AbilityInputActionConfig : InInputConfig->AbilityInputActions)
	{
		if (!AbilityInputActionConfig.IsValid()) continue;
		BindAction(AbilityInputActionConfig.InputAction,
			ETriggerEvent::Started, ContextObject,
			InputPressedFunc,
			AbilityInputActionConfig.InputTag);
		BindAction(AbilityInputActionConfig.InputAction,
			ETriggerEvent::Completed, ContextObject,
			InputReleasedFunc,
			AbilityInputActionConfig.InputTag);
	}
}

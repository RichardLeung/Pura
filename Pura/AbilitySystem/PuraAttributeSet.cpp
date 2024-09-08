// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Pura/Util/PuraDebugHelper.h"
#include "Pura/Util/PuraFunctionLibrary.h"
#include "Pura/Util/PuraGameplayTags.h"

UPuraAttributeSet::UPuraAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
}

void UPuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{;
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage()));
	}
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth() - GetDamageTaken(), 0.0f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		Debug::Print("NewCurrentHealth", NewCurrentHealth);
		// TODO: Notify the UI of the changes
		// TODO: Check if the character is dead
		if(NewCurrentHealth == 0)
		{
			UPuraFunctionLibrary::AddGameplayTagToActorIfNone(GetOwningActor(), PuraGameplayTags::Shared_Status_Dead);
			
		}
	}
}

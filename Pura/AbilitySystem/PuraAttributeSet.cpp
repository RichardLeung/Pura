// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Pura/Component/UI/HeroUIComponent.h"
#include "Pura/Component/UI/PawnUIComponent.h"
#include "Pura/Interface/PawnUIInterface.h"
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
	if(!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Cast<IPawnUIInterface>(Data.Target.GetAvatarActor()));
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s: CachedPawnUIInterface is not valid"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	checkf(PawnUIComponent, TEXT("%s: PawnUIComponent is not valid"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{;
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth()));
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage()));

		if(GetCurrentRage() == GetMaxRage())
		{
			UPuraFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PuraGameplayTags::Player_Status_Rage_Full);
		}
		else if(GetCurrentRage() == 0.f)
		{
			UPuraFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), PuraGameplayTags::Player_Status_Rage_None);
		}
		else
		{
			UPuraFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), PuraGameplayTags::Player_Status_Rage_Full);
			UPuraFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(), PuraGameplayTags::Player_Status_Rage_None);
			
		}
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}
	if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth() - GetDamageTaken(), 0.0f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		// FString DebugMessage = FString::Printf(TEXT("当前目标:%s"), *Data.Target.GetAvatarActor()->GetActorNameOrLabel());
		// Debug::Print(DebugMessage, FColor::Red, 5.f);
		// Debug::Print("NewCurrentHealth", NewCurrentHealth);
		// TODO: Notify the UI of the changes
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		// TODO: Check if the character is dead
		if(GetCurrentHealth() == 0)
		{
			UPuraFunctionLibrary::AddGameplayTagToActorIfNone(GetOwningActor(), PuraGameplayTags::Shared_Status_Dead);
		}
	}
}

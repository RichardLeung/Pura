// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "Kismet/GameplayStatics.h"
#include "Pura/Component/Combat/EnemyCombatComponent.h"
#include "Pura/Component/UI/HeroUIComponent.h"
#include "Pura/Component/UI/PawnUIComponent.h"
#include "Pura/GameInstance/PuraGameInstance.h"
#include "Pura/Interface/PawnCombatInterface.h"
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
	InitAttack(0.f);
	InitDefense(0.f);
	InitCurrentRageStar(0.f);
	InitMaxRageStar(1.f);
	InitCurrentStamina(0.f);
	InitMaxStamina(1.f);
	InitCurrentMana(0.f);
	InitMaxMana(1.f);
	InitStaminaRecoveryRate(1.f);
	InitCriticalHitChance(0.f);
	InitCriticalHitDamage(100.f);
}

void UPuraAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(
			Cast<IPawnUIInterface>(Data.Target.GetAvatarActor()));
	}
	if (!CachedPawnCombatInterface.IsValid())
	{
		CachedPawnCombatInterface = TWeakInterfacePtr<IPawnCombatInterface>(
			Cast<IPawnCombatInterface>(Data.Target.GetAvatarActor()));
	}
	checkf(CachedPawnUIInterface.IsValid(), TEXT("%s: CachedPawnUIInterface is not valid"),
	       *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	checkf(PawnUIComponent, TEXT("%s: PawnUIComponent is not valid"),
	       *Data.Target.GetAvatarActor()->GetActorNameOrLabel());

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		// 当前生命值变化
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.0f, GetMaxHealth()));
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentManaAttribute())
	{
		// 当前法力值变化
		SetCurrentMana(FMath::Clamp(GetCurrentMana(), 0.0f, GetMaxMana()));
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentManaChanged.Broadcast(GetCurrentMana() / GetMaxMana());
		}
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentRageStarAttribute())
	{
		// 当前怒气星值变化
		SetCurrentRageStar(FMath::Clamp(GetCurrentRageStar(), 0.0f, GetMaxRageStar()));
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageStarChanged.Broadcast(GetCurrentRageStar() / GetMaxRageStar());
		}
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		// 当前体力值变化
		SetCurrentStamina(FMath::Clamp(GetCurrentStamina(), 0.0f, GetMaxStamina()));
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentStaminaChanged.Broadcast(GetCurrentStamina() / GetMaxStamina());
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMaxHealthAttribute())
	{
		// 最大生命值变化
		SetMaxHealth(FMath::Max(GetMaxHealth(), GetCurrentHealth()));
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnStatusMaxValueChanged.Broadcast(EPuraHeroStatus::MaxHealth, GetMaxHealth());
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMaxManaAttribute())
	{
		// 最大法力值变化
		SetMaxMana(FMath::Max(GetMaxMana(), GetCurrentMana()));
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnStatusMaxValueChanged.Broadcast(EPuraHeroStatus::MaxMana, GetMaxMana());
		}
	}
	else if (Data.EvaluatedData.Attribute == GetMaxRageStarAttribute())
	{
		// 最大怒气星值变化
		SetMaxRageStar(FMath::Max(GetMaxRageStar(), GetCurrentRageStar()));
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnStatusMaxValueChanged.Broadcast(EPuraHeroStatus::MaxRageStar, GetMaxRageStar());
		}
	}
	else if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		// 当前怒气值变化
		SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.0f, GetMaxRage()));

		if (GetCurrentRage() == GetMaxRage())
		{
			UPuraFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(),
			                                                  PuraGameplayTags::Player_Status_Rage_Full);
		}
		else if (GetCurrentRage() == 0.f)
		{
			UPuraFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(),
			                                                  PuraGameplayTags::Player_Status_Rage_None);
		}
		else
		{
			UPuraFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(),
			                                                        PuraGameplayTags::Player_Status_Rage_Full);
			UPuraFunctionLibrary::RemoveGameplayTagFromActorIfFound(Data.Target.GetAvatarActor(),
			                                                        PuraGameplayTags::Player_Status_Rage_None);
		}
		if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
		{
			HeroUIComponent->OnCurrentRageChanged.Broadcast(GetCurrentRage() / GetMaxRage());
		}
	}
	else if (Data.EvaluatedData.Attribute == GetDamageTakenAttribute())
	{
		const float NewCurrentHealth = FMath::Clamp(GetCurrentHealth() - GetDamageTaken(), 0.0f, GetMaxHealth());
		SetCurrentHealth(NewCurrentHealth);
		PawnUIComponent->OnCurrentHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
		if (GetCurrentHealth() == 0)
		{
			UPuraFunctionLibrary::AddGameplayTagToActorIfNone(GetOwningActor(), PuraGameplayTags::Shared_Status_Dead);

			UEnemyCombatComponent* CombatComponent = Cast<UEnemyCombatComponent>(
				CachedPawnCombatInterface->GetPawnCombatComponent());
			if (CombatComponent)
			{
				FGameplayEventData Payload;
				Payload.Instigator = Data.Target.GetAvatarActor();
				Payload.EventMagnitude = 50.f;
				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(CombatComponent->GetCombatTarget(),
				                                                         PuraGameplayTags::Shared_SetByCaller_IncomeEXP,
				                                                         Payload);
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetIncomeExpAttribute())
	{
		Debug::Print(TEXT("进入经验值变化"));
		const float LocalIncomeXP = GetIncomeExp();
		if (UPuraGameInstance* GameInstance = UPuraFunctionLibrary::GetPuraGameInstance(Data.Target.GetAvatarActor()))
		{
			FPuraLevelExpRow CurrentRow = GameInstance->LevelExpData[GetLevel()];
			if (GetExperience() + LocalIncomeXP >= CurrentRow.RequiredExp)
			{
				FPuraLevelExpRow NextRow = GameInstance->LevelExpData[GetLevel() + 1];
				SetLevel(NextRow.Level);
				SetMaxExperience(NextRow.RequiredExp);
				SetExperience(GetExperience() + LocalIncomeXP - CurrentRow.RequiredExp);
				if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
				{
					HeroUIComponent->OnStatusMaxValueChanged.Broadcast(
						EPuraHeroStatus::Level, GetLevel());
					HeroUIComponent->OnStatusMaxValueChanged.Broadcast(
						EPuraHeroStatus::NextLevelExperience, GetMaxExperience());
				}
			}
			else
			{
				SetExperience(GetExperience() + LocalIncomeXP);
			}
			if (UHeroUIComponent* HeroUIComponent = CachedPawnUIInterface->GetHeroUIComponent())
			{
				HeroUIComponent->OnStatusCurrentValueChanged.Broadcast(
					EPuraHeroStatus::Experience, GetExperience());
			}
		}
		SetIncomeExp(0.f);
	}
}

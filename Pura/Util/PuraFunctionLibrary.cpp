// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "PuraCountDownAction.h"
#include "PuraGameplayTags.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/Character/PuraBaseCharacter.h"
#include "Pura/GameInstance/PuraGameInstance.h"
#include "Pura/SaveGame/PuraSaveGame.h"
#include "Pura/Util/PuraDebugHelper.h"

UPuraAbilitySystemComponent* UPuraFunctionLibrary::NativeGetPuraASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UPuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UPuraFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, const FGameplayTag InTagToAdd)
{
	UPuraAbilitySystemComponent* ASC = NativeGetPuraASCFromActor(InActor);
	if (!ASC->HasMatchingGameplayTag(InTagToAdd))
	{
		ASC->AddLooseGameplayTag(InTagToAdd);
	}
}

void UPuraFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, const FGameplayTag InTagToRemove)
{
	UPuraAbilitySystemComponent* ASC = NativeGetPuraASCFromActor(InActor);
	if (ASC->HasMatchingGameplayTag(InTagToRemove))
	{
		ASC->RemoveLooseGameplayTag(InTagToRemove);
	}
}

bool UPuraFunctionLibrary::NativeDoesActorHaveTag(AActor* InActor, const FGameplayTag InTagToCheck)
{
	UPuraAbilitySystemComponent* ASC = NativeGetPuraASCFromActor(InActor);
	return ASC->HasMatchingGameplayTag(InTagToCheck);
}

void UPuraFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, const FGameplayTag InTagToCheck,
	EPuraConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHaveTag(InActor, InTagToCheck) ? EPuraConfirmType::Yes : EPuraConfirmType::No;
	
}

UPawnCombatComponent* UPuraFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);
	if(IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UPuraFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor,
	EPuraValidType& OutValidType)
{
	UPawnCombatComponent* PawnCombatComponent = NativeGetPawnCombatComponentFromActor(InActor);
	OutValidType = PawnCombatComponent ? EPuraValidType::Valid : EPuraValidType::Invalid;
	return PawnCombatComponent;
}

bool UPuraFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetActor)
{
	check(QueryPawn && TargetActor);
	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetActor->GetController());
	if (QueryTeamAgent && TargetTeamAgent)
	{
		const FGenericTeamId QueryTeamId = QueryTeamAgent->GetGenericTeamId();
		const FGenericTeamId TargetTeamId = TargetTeamAgent->GetGenericTeamId();
		return QueryTeamId != TargetTeamId;
	}
	return false;
}

float UPuraFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UPuraFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim,
	float& OutAngleDifference)
{
	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();
	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	OutAngleDifference = UKismetMathLibrary::DegAcos(DotResult);
	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);
	if (CrossResult.Z > 0.f)
	{
		OutAngleDifference *= -1.f;
	}
	if (OutAngleDifference >= -45.f && OutAngleDifference <= 45.f)
	{
		return PuraGameplayTags::Shared_Status_HitReact_Front;
	}
	else if (OutAngleDifference > 45.f && OutAngleDifference <= 135.f)
	{
		return PuraGameplayTags::Shared_Status_HitReact_Left;
	}
	else if (OutAngleDifference < -45.f && OutAngleDifference >= -135.f)
	{
		return PuraGameplayTags::Shared_Status_HitReact_Right;
	}
	else if (OutAngleDifference > 135.f || OutAngleDifference < -135.f)
	{
		return PuraGameplayTags::Shared_Status_HitReact_Back;
	}
	return PuraGameplayTags::Shared_Status_HitReact_Front;
}

bool UPuraFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefender)
{
	check(InAttacker && InDefender);
	const FVector AttackerForward = InAttacker->GetActorForwardVector();
	const FVector DefenderForward = InDefender->GetActorForwardVector();
	const float DotResult = FVector::DotProduct(AttackerForward, DefenderForward);
	// const FString DebugString = FString::Printf(TEXT("DotResult: %f     Result: %s"), DotResult, DotResult < 0.1f ? TEXT("Is Valid") : TEXT("Is Not Valid"));
	// Debug::Print(DebugString);
	return DotResult < -0.1f;
}

bool UPuraFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(AActor* InInstigator, AActor* InTarget,
	const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle)
{
	check(InInstigator && InTarget);
	UPuraAbilitySystemComponent* SourceASC = NativeGetPuraASCFromActor(InInstigator);
	UPuraAbilitySystemComponent* TargetASC = NativeGetPuraASCFromActor(InTarget);
	FActiveGameplayEffectHandle ActiveGameplayEffectHandle = SourceASC->ApplyGameplayEffectSpecToTarget(*InGameplayEffectSpecHandle.Data, TargetASC);
	return ActiveGameplayEffectHandle.WasSuccessfullyApplied();
}

void UPuraFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
	float& OutRemainingTime, EPuraCountDownActionInput CountDownInput, UPARAM(DisplayName="Output") EPuraCountDownActionOutput& CountDownOutput,
	FLatentActionInfo LatentInfo)
{
	UWorld* World = nullptr;
	if(GEngine)
	{
		World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	}
	if(!World)
	{
		return;
	}
	FLatentActionManager& LatentActionManager = World->GetLatentActionManager();
	FPuraCountDownAction* FoundAction = LatentActionManager.FindExistingAction<FPuraCountDownAction>(LatentInfo.CallbackTarget, LatentInfo.UUID);
	if(CountDownInput == EPuraCountDownActionInput::Start)
	{
		if (!FoundAction)
		{
			LatentActionManager.AddNewAction(
				LatentInfo.CallbackTarget,
				LatentInfo.UUID,
				new FPuraCountDownAction(
					TotalTime,
					UpdateInterval,
					OutRemainingTime,
					CountDownOutput,
					LatentInfo
					));
		}
	}
	if(CountDownInput == EPuraCountDownActionInput::Cancel)
	{
		if(FoundAction)
		{
			FoundAction->CancelAction();
		}
	}
}

UPuraGameInstance* UPuraFunctionLibrary::GetPuraGameInstance(const UObject* WorldContextObject)
{
	if (GEngine)
	{
		if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			return World->GetGameInstance<UPuraGameInstance>();
		}
	}
	return nullptr;
}

void UPuraFunctionLibrary::ToggleInputMode(const UObject* WorldContextObject, EPuraInputMode InputMode)
{
	APlayerController* PlayerController = nullptr;
	if (GEngine)
	{
		if(UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
		{
			PlayerController = World->GetFirstPlayerController();
		}
	}
	if (PlayerController)
	{
		if (InputMode == EPuraInputMode::GameOnly)
		{
			PlayerController->SetInputMode(FInputModeGameOnly());
			PlayerController->bShowMouseCursor = false;
		}
		else if(InputMode == EPuraInputMode::UIOnly)
		{
			PlayerController->SetInputMode(FInputModeUIOnly());
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void UPuraFunctionLibrary::SaveCurrentGameDifficulty(EPuraGameDifficulty CurrentGameDifficulty)
{
	USaveGame* SaveGameObject = UGameplayStatics::CreateSaveGameObject(UPuraSaveGame::StaticClass());
	if (UPuraSaveGame* PuraSaveGameObject = Cast<UPuraSaveGame>(SaveGameObject))
	{
		PuraSaveGameObject->SavedCurrentGameDifficulty = CurrentGameDifficulty;
		const bool bWasSaved = UGameplayStatics::SaveGameToSlot(PuraSaveGameObject, PuraGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString(), 0);
	}
}

bool UPuraFunctionLibrary::TryLoadSavedGameDifficulty(EPuraGameDifficulty& OutSavedGameDifficulty)
{
	const FString SlotName = PuraGameplayTags::GameData_SaveGame_Slot_1.GetTag().ToString();
	if (UGameplayStatics::DoesSaveGameExist(SlotName, 0))
	{
		USaveGame* SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, 0);
		if (const UPuraSaveGame* PuraSaveGameObject = Cast<UPuraSaveGame>(SaveGameObject))
		{
			OutSavedGameDifficulty = PuraSaveGameObject->SavedCurrentGameDifficulty;
			return true;
		}
	}
	return false;
}
	
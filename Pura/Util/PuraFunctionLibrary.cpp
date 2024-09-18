// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/Character/PuraBaseCharacter.h"

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
	
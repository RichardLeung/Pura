// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PuraEnumType.h"
#include "PuraFunctionLibrary.generated.h"

class UPuraGameInstance;
struct FGameplayEffectSpecHandle;
struct FGameplayTag;
struct FScalableFloat;
class UPawnCombatComponent;
class UPuraAbilitySystemComponent;

/**
 * 
 */
UCLASS()
class PURA_API UPuraFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	static UPuraAbilitySystemComponent* NativeGetPuraASCFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Pura|FunctionLibrary")
	static void AddGameplayTagToActorIfNone(AActor* InActor, const FGameplayTag InTagToAdd);

	UFUNCTION(BlueprintCallable, Category = "Pura|FunctionLibrary")
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor, const FGameplayTag InTagToRemove);

	static bool NativeDoesActorHaveTag(AActor* InActor, const FGameplayTag InTagToCheck);

	UFUNCTION(BlueprintCallable, Category = "Pura|FunctionLibrary", meta=(DisplayName="Does Actor Have Tag", ExpandEnumAsExecs="OutConfirmType"))
	static void BP_DoesActorHaveTag(AActor* InActor, const FGameplayTag InTagToCheck, EPuraConfirmType& OutConfirmType);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, Category = "Pura|FunctionLibrary", meta=(DisplayName="Get Pawn Combat Component From Actor", ExpandEnumAsExecs="OutValidType"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor, EPuraValidType& OutValidType);

	UFUNCTION(BlueprintPure, Category = "Pura|FunctionLibrary")
	static bool IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetActor);

	UFUNCTION(BlueprintPure, Category = "Pura|FunctionLibrary", meta=(CompactNodeTitle="Get Value At Level"))
	static float GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel = 1.f);

	UFUNCTION(BlueprintPure, Category = "Pura|FunctionLibrary")
	static FGameplayTag ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OutAngleDifference);

	UFUNCTION(BlueprintPure, Category = "Pura|FunctionLibrary")
	static bool IsValidBlock(AActor* InAttacker, AActor* InDefender);

	UFUNCTION(BlueprintCallable, Category = "Pura|FunctionLibrary")
	static bool ApplyGameplayEffectSpecHandleToTarget(AActor* InInstigator, AActor* InTarget,const FGameplayEffectSpecHandle& InGameplayEffectSpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Pura|FunctionLibrary",
		meta=(Latent, WorldContext="WorldContextObject", LatentInfo="LatentInfo", ExpandEnumAsExecs="CountDownInput|CountDownOutput", TotalTime="1.0", UpdateInterval="0.1"))
	static void CountDown(
		const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
		float& OutRemainingTime,
		EPuraCountDownActionInput CountDownInput,
		UPARAM(DisplayName="Output") EPuraCountDownActionOutput& CountDownOutput,
		FLatentActionInfo LatentInfo);

	UFUNCTION(BlueprintPure, Category = "Pura|FunctionLibrary", meta = (WorldContext = "WorldContextObject"))
	static UPuraGameInstance* GetPuraGameInstance(const UObject* WorldContextObject);
};

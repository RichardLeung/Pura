// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PuraFunctionLibrary.generated.h"

class UPuraAbilitySystemComponent;

UENUM()
enum class EPuraConfirmType : uint8
{
	Yes,
	No,
};
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
};

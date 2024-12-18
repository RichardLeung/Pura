﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "Pura/Interface/PawnCombatInterface.h"
#include "Pura/Interface/PawnUIInterface.h"
#include "PuraBaseCharacter.generated.h"

class UDataAsset_StartUpBase;
class UPuraAttributeSet;
class UPuraAbilitySystemComponent;
class UMotionWarpingComponent;

UCLASS()
class PURA_API APuraBaseCharacter : public ACharacter, public IAbilitySystemInterface, public IPawnCombatInterface, public IPawnUIInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuraBaseCharacter();

	virtual void PossessedBy(AController* NewController) override;

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	// Implement IPawnCombatInterface
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;

protected:	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UPuraAbilitySystemComponent* PuraAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "MotionWarping")
	UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AbilitySystem")
	UPuraAttributeSet* PuraAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpBase> CharacterStartUpData;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// 暂停
	virtual void Pause();

public:
	FORCEINLINE UPuraAbilitySystemComponent* GetPuraAbilitySystemComponent() const  { return PuraAbilitySystemComponent; }

	FORCEINLINE UPuraAttributeSet* GetPuraAttributeSet() const { return PuraAttributeSet; }
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "PuraBaseCharacter.generated.h"

class UDataAsset_StartUpBase;
class UPuraAttributeSet;
class UPuraAbilitySystemComponent;

UCLASS()
class PURA_API APuraBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuraBaseCharacter();

	virtual void PossessedBy(AController* NewController) override;

	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	UPuraAbilitySystemComponent* PuraAbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = AbilitySystem)
	UPuraAttributeSet* PuraAttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = CharacterData)
	TSoftObjectPtr<UDataAsset_StartUpBase> CharacterStartUpData;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	FORCEINLINE UPuraAbilitySystemComponent* GetPuraAbilitySystemComponent() const  { return PuraAbilitySystemComponent; }

	FORCEINLINE UPuraAttributeSet* GetPuraAttributeSet() const { return PuraAttributeSet; }
};

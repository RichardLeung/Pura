// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraBaseCharacter.h"
#include "PuraEnemyCharacter.generated.h"

class UEnemyCombatComponent;

UCLASS()
class PURA_API APuraEnemyCharacter : public APuraBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuraEnemyCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

public:
	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const { return EnemyCombatComponent; }
};

﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraBaseCharacter.h"
#include "PuraEnemyCharacter.generated.h"

class UWidgetComponent;
class UEnemyCombatComponent;
class UEnemyUIComponent;

UCLASS()
class PURA_API APuraEnemyCharacter : public APuraBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuraEnemyCharacter();

	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;

	UEnemyCombatComponent* GetEnemyCombatComponent() const;

	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	UEnemyUIComponent* GetEnemyUIComponent() const;

protected:
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat")
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* EnemyHealthWidgetComponent;
	
private:
	void InitEnemyStartUpData();
};

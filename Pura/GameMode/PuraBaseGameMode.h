// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Pura/Util/PuraEnumType.h"
#include "PuraBaseGameMode.generated.h"
/**
 * 
 */
UCLASS()
class PURA_API APuraBaseGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APuraBaseGameMode();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Game Settings")
	EPuraGameDifficulty CurrentGameDifficulty;

public:
	FORCEINLINE EPuraGameDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty; }
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Pura/Util/PuraEnumType.h"
#include "PuraSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class PURA_API UPuraSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 SavedCurrentGameDifficulty;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "PuraHeroController.generated.h"

/**
 * 
 */
UCLASS()
class PURA_API APuraHeroController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	APuraHeroController();

	//~ Begin IGenericTeamAgentInterface begin
	virtual FGenericTeamId GetGenericTeamId() const override;
	//~ End IGenericTeamAgentInterface end

private:
	FGenericTeamId HeroTeamID;
};

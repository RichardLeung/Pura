// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraHeroController.h"

#include "EnhancedInputSubsystems.h"

APuraHeroController::APuraHeroController()
{
	HeroTeamID = FGenericTeamId(0);
}

void APuraHeroController::BeginPlay()
{
	Super::BeginPlay();
}


FGenericTeamId APuraHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}

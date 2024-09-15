// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraHeroController.h"

APuraHeroController::APuraHeroController()
{
	HeroTeamID = FGenericTeamId(0);
}

FGenericTeamId APuraHeroController::GetGenericTeamId() const
{
	return HeroTeamID;
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraBaseCharacter.h"


// Sets default values
APuraBaseCharacter::APuraBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;
}

// Called when the game starts or when spawned
void APuraBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraBaseCharacter.h"

#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/AbilitySystem/PuraAttributeSet.h"


// Sets default values
APuraBaseCharacter::APuraBaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;
	GetMesh()->bReceivesDecals = false;
	PuraAttributeSet = CreateDefaultSubobject<UPuraAttributeSet>(TEXT("PuraAttributeSet"));
	PuraAbilitySystemComponent = CreateDefaultSubobject<UPuraAbilitySystemComponent>(TEXT("PuraAbilitySystemComponent"));
}

void APuraBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(PuraAbilitySystemComponent)
	{
		PuraAbilitySystemComponent->InitAbilityActorInfo(this, this);
		ensureMsgf(!CharacterStartUpData.IsNull(), TEXT("Forgot to assign start up data to %s"), *GetName());
	}
}

UAbilitySystemComponent* APuraBaseCharacter::GetAbilitySystemComponent() const
{
	return GetPuraAbilitySystemComponent();
}

UPawnCombatComponent* APuraBaseCharacter::GetPawnCombatComponent() const
{
	return nullptr;
}

// Called when the game starts or when spawned
void APuraBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


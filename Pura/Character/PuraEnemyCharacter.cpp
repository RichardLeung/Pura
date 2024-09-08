// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraEnemyCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pura/Component/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "Pura/Component/UI/EnemyUIComponent.h"
#include "Pura/DataAsset/DataAsset_EnemyStartUpData.h"
#include "Pura/Util/PuraDebugHelper.h"

// Sets default values
APuraEnemyCharacter::APuraEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
	
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>(TEXT("EnemyCombatComponent"));

	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>(TEXT("EnemyUIComponent"));
}

UPawnCombatComponent* APuraEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* APuraEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

void APuraEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
}

void APuraEnemyCharacter::InitEnemyStartUpData()
{
	if(CharacterStartUpData.IsNull()) return;

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UDataAsset_StartUpBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(PuraAbilitySystemComponent);
				}
			}
		)
	);
}


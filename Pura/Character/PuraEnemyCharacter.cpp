// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraEnemyCharacter.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Pura/Component/Combat/EnemyCombatComponent.h"
#include "Engine/AssetManager.h"
#include "Pura/Component/UI/EnemyUIComponent.h"
#include "Pura/DataAsset/DataAsset_EnemyStartUpData.h"
#include "Pura/GameMode/PuraBaseGameMode.h"
#include "Pura/Util/PuraDebugHelper.h"
#include "Pura/Util/PuraFunctionLibrary.h"
#include "Pura/Widget/PuraUserWidgetBase.h"

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

	EnemyHealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("EnemyHealthWidgetComponent"));
	EnemyHealthWidgetComponent->SetupAttachment(GetMesh());

	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuraEnemyCharacter::OnLeftHandCollisionBoxOverlapBegin);
	LeftHandCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &APuraEnemyCharacter::OnLeftHandCollisionBoxOverlapEnd);
	
	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &APuraEnemyCharacter::OnRightHandCollisionBoxOverlapBegin);
	RightHandCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &APuraEnemyCharacter::OnRightHandCollisionBoxOverlapEnd);
}

UPawnCombatComponent* APuraEnemyCharacter::GetPawnCombatComponent() const
{
	return EnemyCombatComponent;
}

UPawnUIComponent* APuraEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* APuraEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void APuraEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	if(UPuraUserWidgetBase* HealthWidget = Cast<UPuraUserWidgetBase>(EnemyHealthWidgetComponent->GetUserWidgetObject()))
	{
		HealthWidget->InitEnemyCreatedWidget(this);
	}
}

void APuraEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	InitEnemyStartUpData();
}

#if WITH_EDITOR
void APuraEnemyCharacter::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	if(PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxSocketName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxSocketName);
	}
	else if(PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxSocketName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxSocketName);
	}
}
#endif

void APuraEnemyCharacter::OnLeftHandCollisionBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent,
                                                             AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                             const FHitResult& SweepResult)
{
	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(UPuraFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			EnemyCombatComponent->OnWeaponHitTargetActor(HitPawn);
		}
	}
}

void APuraEnemyCharacter::OnLeftHandCollisionBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void APuraEnemyCharacter::OnRightHandCollisionBoxOverlapBegin(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if(UPuraFunctionLibrary::IsTargetPawnHostile(this, HitPawn))
		{
			EnemyCombatComponent->OnWeaponHitTargetActor(HitPawn);
		}
	}
}

void APuraEnemyCharacter::OnRightHandCollisionBoxOverlapEnd(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void APuraEnemyCharacter::InitEnemyStartUpData()
{
	if(CharacterStartUpData.IsNull()) return;
	int32 AbilityApplyLevel = 1;
	if (APuraBaseGameMode* BaseGameMode = GetWorld()->GetAuthGameMode<APuraBaseGameMode>())
	{
		switch (BaseGameMode->GetCurrentGameDifficulty())
		{
		case EPuraGameDifficulty::Easy:
			AbilityApplyLevel = 1;
			break;
		case EPuraGameDifficulty::Normal:
			AbilityApplyLevel = 2;
			break;
		case EPuraGameDifficulty::Hard:
			AbilityApplyLevel = 3;
			break;
		case EPuraGameDifficulty::VeryHard:
			AbilityApplyLevel = 4;
			break;
		default:
			break;
		}
	}
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda(
			[this, AbilityApplyLevel]()
			{
				if (UDataAsset_StartUpBase* LoadedData = CharacterStartUpData.Get())
				{
					LoadedData->GiveToAbilitySystemComponent(PuraAbilitySystemComponent, AbilityApplyLevel);
				}
			}
		)
	);
}


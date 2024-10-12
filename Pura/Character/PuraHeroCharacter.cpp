// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraHeroCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Pura/DataAsset/DataAsset_InputConfig.h"
#include "Pura/Input/PuraInputComponent.h"
#include "Pura/Util/PuraDebugHelper.h"
#include "Pura/Util/PuraGameplayTags.h"
#include "Pura/AbilitySystem/PuraAbilitySystemComponent.h"
#include "Pura/AbilitySystem/PuraAttributeSet.h"
#include "Pura/Component/Combat/HeroCombatComponent.h"
#include "Pura/Component/UI/HeroUIComponent.h"
#include "Pura/DataAsset/DataAsset_StartUpBase.h"
#include "Pura/GameMode/PuraBaseGameMode.h"

// Sets default values
APuraHeroCharacter::APuraHeroCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 55.0f, 65.0f);
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));	
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 400.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	HeroCombatComponent = CreateDefaultSubobject<UHeroCombatComponent>(TEXT("HeroCombatComponent"));

	HeroUIComponent = CreateDefaultSubobject<UHeroUIComponent>(TEXT("HeroUIComponent"));
}

UPawnCombatComponent* APuraHeroCharacter::GetPawnCombatComponent() const
{
	return HeroCombatComponent;
}

UPawnUIComponent* APuraHeroCharacter::GetPawnUIComponent() const
{
	return HeroUIComponent;
}

UHeroUIComponent* APuraHeroCharacter::GetHeroUIComponent() const
{
	return HeroUIComponent;
}

// Called when the game starts or when spawned
void APuraHeroCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APuraHeroCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	if(!CharacterStartUpData.IsNull())
	{
		if(UDataAsset_StartUpBase* LoadedData = CharacterStartUpData.LoadSynchronous())
		{
			int32 AbilityApplyLevel = 1;
			LoadedData->GiveToAbilitySystemComponent(PuraAbilitySystemComponent, AbilityApplyLevel);
		}
	}
}

// Called every frame
void APuraHeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APuraHeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(InputConfigDataAsset, TEXT("InputConfigDataAsset is nullptr"));
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	UPuraInputComponent* PuraInputComponent = CastChecked<UPuraInputComponent>(PlayerInputComponent);
	PuraInputComponent->BindNativeInputAction(InputConfigDataAsset, PuraGameplayTags::InputTag_Move, ETriggerEvent::Triggered, this, &ThisClass::Input_Move);
	PuraInputComponent->BindNativeInputAction(InputConfigDataAsset, PuraGameplayTags::InputTag_Look, ETriggerEvent::Triggered, this, &ThisClass::Input_Look);
	PuraInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
	PuraInputComponent->BindNativeInputAction(InputConfigDataAsset, PuraGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Triggered, this, &ThisClass::Input_SwitchTargetTriggered);
	PuraInputComponent->BindNativeInputAction(InputConfigDataAsset, PuraGameplayTags::InputTag_SwitchTarget, ETriggerEvent::Completed, this, &ThisClass::Input_SwitchTargetCompleted);
	PuraInputComponent->BindNativeInputAction(InputConfigDataAsset, PuraGameplayTags::InputTag_PickUp_Stone, ETriggerEvent::Started, this, &ThisClass::Input_PickUpStoneStarted);
}

void APuraHeroCharacter::Input_Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	if(MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}
	if(MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void APuraHeroCharacter::Input_Look(const FInputActionValue& Value)
{
	const FVector2D LookVector = Value.Get<FVector2D>();
	if(LookVector.X != 0)
	{
		AddControllerYawInput(LookVector.X);
	}
	if(LookVector.Y != 0)
	{
		AddControllerPitchInput(LookVector.Y);
	}
}

void APuraHeroCharacter::Input_SwitchTargetTriggered(const FInputActionValue& Value)
{
	SwitchDirection = Value.Get<FVector2D>();
}

void APuraHeroCharacter::Input_SwitchTargetCompleted(const FInputActionValue& Value)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		SwitchDirection.X > 0.f ? PuraGameplayTags::Player_Event_SwitchTarget_Right : PuraGameplayTags::Player_Event_SwitchTarget_Left,
		Data
		);
}

void APuraHeroCharacter::Input_PickUpStoneStarted(const FInputActionValue& Value)
{
	FGameplayEventData Data;
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
		this,
		PuraGameplayTags::Player_Event_ConsumeStone,
		Data);
}

void APuraHeroCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	PuraAbilitySystemComponent->OnAbilityInputPressed(InInputTag);
}

void APuraHeroCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	PuraAbilitySystemComponent->OnAbilityInputReleased(InInputTag);
}


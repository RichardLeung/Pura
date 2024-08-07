// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraBaseCharacter.h"
#include "PuraHeroCharacter.generated.h"

struct FInputActionValue;
class UCameraComponent;
class USpringArmComponent;
class UDataAsset_InputConfig;

UCLASS()
class PURA_API APuraHeroCharacter : public APuraBaseCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuraHeroCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
#pragma endregion

	

#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta = (AllowPrivateAccess = "true"))
	UDataAsset_InputConfig* InputConfigDataAsset;
	
	void Input_Move(const FInputActionValue& Value);
	
	void Input_Look(const FInputActionValue& Value);
	
#pragma endregion
};

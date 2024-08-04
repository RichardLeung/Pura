// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PuraBaseCharacter.generated.h"

UCLASS()
class PURA_API APuraBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APuraBaseCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};

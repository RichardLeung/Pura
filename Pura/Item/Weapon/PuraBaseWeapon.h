// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PuraBaseWeapon.generated.h"

class UBoxComponent;

UCLASS()
class PURA_API APuraBaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuraBaseWeapon();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Weapon)
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Weapon)
	UBoxComponent* WeaponCollisionBox;

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const
	{
		return WeaponCollisionBox;
	};
};

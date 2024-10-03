// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "PuraProjectileBase.generated.h"

class UBoxComponent;
class UNiagaraComponent;
class UProjectileMovementComponent;
struct FGameplayEventData;

UENUM()
enum class EProjectileDamagePolicy: uint8
{
	OnHit,
	OnBeginOverlap,
};

UCLASS()
class PURA_API APuraProjectileBase : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APuraProjectileBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	UBoxComponent* ProjectileCollisionBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	UNiagaraComponent* ProjectileNiagaraComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Projectile")
	EProjectileDamagePolicy DamagePolicy = EProjectileDamagePolicy::OnHit;

	UPROPERTY(BlueprintReadOnly, Category="Projectile", meta=(ExposeOnSpawn = "true"))
	FGameplayEffectSpecHandle ProjectileDamageEffectHandle;

	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UFUNCTION()
	virtual void OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnProjectileEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Spawn Projectile Hit FX"))
	void BP_OnSpawnProjectileHitFX(const FVector& HitLocation);

private:
	void HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload);

	TArray<AActor*> OverlappedActors;
};

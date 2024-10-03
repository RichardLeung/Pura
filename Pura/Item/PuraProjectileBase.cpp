// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Components/BoxComponent.h"
#include "NiagaraComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Pura/Util/PuraDebugHelper.h"
#include "Pura/Util/PuraFunctionLibrary.h"
#include "Pura/Util/PuraGameplayTags.h"

APuraProjectileBase::APuraProjectileBase()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileCollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("ProjectileCollisionBox"));
	SetRootComponent(ProjectileCollisionBox);
	ProjectileCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	ProjectileCollisionBox->OnComponentHit.AddUniqueDynamic(this, &ThisClass::OnProjectileHit);
	ProjectileCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileBeginOverlap);
	ProjectileCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnProjectileEndOverlap);

	ProjectileNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>(TEXT("ProjectileNiagaraComponent"));
	ProjectileNiagaraComponent->SetupAttachment(GetRootComponent());

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->InitialSpeed = 700.0f;
	ProjectileMovementComponent->MaxSpeed = 900.0f;
	ProjectileMovementComponent->Velocity = FVector(1.f,0.f,0.f);
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;

	InitialLifeSpan = 4.f;
}

void APuraProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	if(DamagePolicy == EProjectileDamagePolicy::OnBeginOverlap)
	{
		ProjectileCollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
	
}

void APuraProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	BP_OnSpawnProjectileHitFX(Hit.ImpactPoint);
	APawn* HitPawn = Cast<APawn>(OtherActor);
	if(!HitPawn || !UPuraFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
	{
		Debug::Print("Miss");
		Destroy();
		return;
	}
	bool bIsValidBlock = false;
	const bool bIsPlayerBlocking = UPuraFunctionLibrary::NativeDoesActorHaveTag(HitPawn, PuraGameplayTags::Player_Status_Blocking);
	if(bIsPlayerBlocking)
	{
		bIsValidBlock = UPuraFunctionLibrary::IsValidBlock(this, HitPawn);
	}
	FGameplayEventData EventData;
	EventData.Instigator = this;
	EventData.Target = HitPawn;
	if(bIsValidBlock)
	{
		Debug::Print("SuccessfulBlock");
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitPawn,
			PuraGameplayTags::Player_Event_SuccessfulBlock,
			EventData
		);
	}else
	{
		HandleApplyProjectileDamage(HitPawn, EventData);
	}
	Destroy();
}

void APuraProjectileBase::OnProjectileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor))
	{
		return;
	}
	OverlappedActors.AddUnique(OtherActor);
	if(APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		FGameplayEventData EventData;
		EventData.Instigator = GetInstigator();
		EventData.Target = HitPawn;
		
		if(UPuraFunctionLibrary::IsTargetPawnHostile(GetInstigator(), HitPawn))
		{
			HandleApplyProjectileDamage(HitPawn, EventData);
		}
	}
}

void APuraProjectileBase::OnProjectileEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void APuraProjectileBase::HandleApplyProjectileDamage(APawn* InHitPawn, const FGameplayEventData& InPayload)
{
	checkf(ProjectileDamageEffectHandle.IsValid(),TEXT("Forgot to set ProjectileDamageEffectHandle to the projectile: %s"), *GetActorNameOrLabel());
	if(const bool bWasApplied = UPuraFunctionLibrary::ApplyGameplayEffectSpecHandleToTarget(GetInstigator(), InHitPawn, ProjectileDamageEffectHandle))
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			InHitPawn,
			PuraGameplayTags::Shared_Event_HitReact,
			InPayload
		);
	}
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Pura/Util/PuraDebugHelper.h"

APuraAIController::APuraAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	if(UCrowdFollowingComponent* CrowdComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		Debug::Print("CrowdFollowingComponent is set", FColor::Green);
	}

	AISightConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("EnemySightConfig_Sight"));
	AISightConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISightConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISightConfig_Sight->SightRadius = 5000.f;
	AISightConfig_Sight->LoseSightRadius = 0.f;
	AISightConfig_Sight->PeripheralVisionAngleDegrees = 360.f;

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	EnemyPerceptionComponent->ConfigureSense(*AISightConfig_Sight);
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &APuraAIController::OnEnemyPerceptionUpdated);

	SetGenericTeamId(FGenericTeamId(1));
}

void APuraAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if(Stimulus.WasSuccessfullySensed() && Actor)
	{
		if(UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
		}
	}
}

ETeamAttitude::Type APuraAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(PawnToCheck->GetController());
	if(OtherTeamAgent && OtherTeamAgent->GetGenericTeamId().GetId() != GetGenericTeamId().GetId())
	{
		return ETeamAttitude::Hostile;
	}
	return ETeamAttitude::Friendly;
}
	
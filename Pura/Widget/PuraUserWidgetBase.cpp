// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraUserWidgetBase.h"
#include "Pura/Interface/PawnUIInterface.h"
#include "Pura/Util/PuraDebugHelper.h"

void UPuraUserWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if(IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if(UHeroUIComponent* HeroUIComponent = PawnUIInterface->GetHeroUIComponent())
		{
			BP_OnOwningHeroUIComponentInitialized(HeroUIComponent);
		}
	}
}

void UPuraUserWidgetBase::InitEnemyCreatedWidget(AActor* OwningEnemyActor)
{
	if(IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(OwningEnemyActor))
	{
		if(UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent())
		{
			BP_OnOwningEnemyUIComponentInitialized(EnemyUIComponent);
		}
	}
}

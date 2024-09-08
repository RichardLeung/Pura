// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraUserWidgetBase.h"
#include "Pura/Interface/PawnUIInterface.h"

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

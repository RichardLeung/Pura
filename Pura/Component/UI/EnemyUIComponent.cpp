// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyUIComponent.h"
#include "Pura/Widget/PuraCommonUserWidgetBase.h"
#include "Pura/Widget/PuraUserWidgetBase.h"


void UEnemyUIComponent::RegisterEnemyDrawnWidget(UPuraCommonUserWidgetBase* InWidgetToRegister)
{
	EnemyDrawnWidgets.Add(InWidgetToRegister);
}

void UEnemyUIComponent::RemoveEnemyDrawnWidgetsIfAny()
{
    if(EnemyDrawnWidgets.IsEmpty())
    {
        return;
    }
	for (UPuraCommonUserWidgetBase* DrawnWidget : EnemyDrawnWidgets)
    {
        if (DrawnWidget)
        {
            DrawnWidget->RemoveFromParent();
        }
    }
    EnemyDrawnWidgets.Empty();
}

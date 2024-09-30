// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnUIComponent.h"
#include "EnemyUIComponent.generated.h"

class UPuraUserWidgetBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PURA_API UEnemyUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void RegisterEnemyDrawnWidget(UPuraUserWidgetBase* InWidgetToRegister);

	UFUNCTION(BlueprintCallable)
	void RemoveEnemyDrawnWidgetsIfAny();

private:
	TArray<UPuraUserWidgetBase*> EnemyDrawnWidgets;
};

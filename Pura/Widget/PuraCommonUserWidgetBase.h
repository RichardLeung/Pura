// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonUserWidget.h"
#include "PuraCommonUserWidgetBase.generated.h"

class UEnemyUIComponent;
class UHeroUIComponent;

/**
 * 
 */
UCLASS()
class PURA_API UPuraCommonUserWidgetBase : public UCommonUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Hero UI Component Initialized"))
	void BP_OnOwningHeroUIComponentInitialized(UHeroUIComponent* OwningHeroUIComponent);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Owning Enemy UI Component Initialized"))
	void BP_OnOwningEnemyUIComponentInitialized(UEnemyUIComponent* OwningEnemyUIComponent);

public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyCreatedWidget(AActor* OwningEnemyActor);
};

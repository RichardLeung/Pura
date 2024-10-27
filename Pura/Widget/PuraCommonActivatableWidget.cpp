// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraCommonActivatableWidget.h"

TOptional<FUIInputConfig> UPuraCommonActivatableWidget::GetDesiredInputConfig() const
{
	switch (InputConfig)
	{
	case EPuraWidgetInputMode::GameAndMenu:
		return FUIInputConfig(ECommonInputMode::All, GameMouseCaptureMode);
	case EPuraWidgetInputMode::Game:
		return FUIInputConfig(ECommonInputMode::Game, GameMouseCaptureMode);
	case EPuraWidgetInputMode::Menu:
		return FUIInputConfig(ECommonInputMode::Menu, EMouseCaptureMode::NoCapture);
	case EPuraWidgetInputMode::Default:
	default:
		return TOptional<FUIInputConfig>();
	}
}

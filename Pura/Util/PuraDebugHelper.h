// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

namespace Debug
{
	static void Print(const FString& message, const FColor& Color = FColor::MakeRandomColor(), int32 InKey = -1)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 5.f, Color, message);
			UE_LOG(LogTemp, Warning, TEXT("%s"), *message);
		}
	}
}

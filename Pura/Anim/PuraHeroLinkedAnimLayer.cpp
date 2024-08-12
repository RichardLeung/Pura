// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraHeroLinkedAnimLayer.h"

#include "PuraHeroAnimInstance.h"

UPuraHeroAnimInstance* UPuraHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
	return Cast<UPuraHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());
}

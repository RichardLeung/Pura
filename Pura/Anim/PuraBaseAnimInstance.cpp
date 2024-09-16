// Fill out your copyright notice in the Description page of Project Settings.


#include "PuraBaseAnimInstance.h"
#include "Pura/Util/PuraFunctionLibrary.h"

bool UPuraBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagToCheck) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
    {
        return UPuraFunctionLibrary::NativeDoesActorHaveTag(OwningPawn, TagToCheck);
    }
	return false;
}

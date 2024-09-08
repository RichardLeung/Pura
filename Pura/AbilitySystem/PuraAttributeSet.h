// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "PuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

class IPawnUIInterface;
/**
 * 
 */
UCLASS()
class PURA_API UPuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPuraAttributeSet();

	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, CurrentHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, CurrentRage)

	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, MaxRage)

	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, AttackPower)

	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, DefensePower)

	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, DamageTaken)

private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
};

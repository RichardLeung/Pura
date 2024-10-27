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

	// 当前等级
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData Level;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, Level)

	// 当前经验值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData Experience;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, Experience)

	// 最大经验值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData MaxExperience;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, MaxExperience)

	// 当前生命值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, CurrentHealth)

	// 最大生命值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, MaxHealth)

	// 当前怒气值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData CurrentRage;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, CurrentRage)

	// 最大怒气值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData MaxRage;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, MaxRage)

	// 当前怒气星值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData CurrentRageStar;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, CurrentRageStar)

	// 最大怒气星值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData MaxRageStar;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, MaxRageStar)

	// 当前法力值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData CurrentMana;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, CurrentMana)

	// 最大法力值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, MaxMana)

	// 攻击力
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData Attack;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, Attack)

	// 防御力
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData Defense;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, Defense)

	// 伤害
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData DamageTaken;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, DamageTaken)

	// 当前气力值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, CurrentStamina)

	// 最大气力值
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, MaxStamina)
	

	// 气力恢复
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData StaminaRecoveryRate;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, StaminaRecoveryRate)

	// 暴击率
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, CriticalHitChance)
	
	// 暴击伤害
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, CriticalHitDamage)

	// 伤害加成
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData DamageBonus;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, DamageBonus)
	
	// 伤害减免
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData DamageReduction;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, DamageReduction)
	
	// 冰霜抗性
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData FrostResistance;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, FrostResistance)
	
	// 火焰抗性
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData FireResistance;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, FireResistance)
	
	// 闪电抗性
	UPROPERTY(BlueprintReadOnly, Category = "Pura|Attribute")
	FGameplayAttributeData LightningResistance;
	ATTRIBUTE_ACCESSORS(UPuraAttributeSet, LightningResistance)

private:
	TWeakInterfacePtr<IPawnUIInterface> CachedPawnUIInterface;
};

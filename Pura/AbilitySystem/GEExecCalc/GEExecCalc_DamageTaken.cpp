// Fill out your copyright notice in the Description page of Project Settings.


#include "GEExecCalc_DamageTaken.h"
#include "Pura/AbilitySystem/PuraAttributeSet.h"
#include "Pura/Util/PuraDebugHelper.h"
#include "Pura/Util/PuraGameplayTags.h"

struct FPuraDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);
	FPuraDamageCapture()
    {
        DEFINE_ATTRIBUTE_CAPTUREDEF(UPuraAttributeSet, AttackPower, Source, false);
        DEFINE_ATTRIBUTE_CAPTUREDEF(UPuraAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPuraAttributeSet, DamageTaken, Target, false);
    }
};

static const FPuraDamageCapture& GetPuraDamageCapture()
{
    static FPuraDamageCapture PuraDamageCapture;
    return PuraDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/* Slow way of doing capture */
	// FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	// 	UPuraAttributeSet::StaticClass(),
	// 	GET_MEMBER_NAME_CHECKED(UPuraAttributeSet, AttackPower)
	// );
	// FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	// 	AttackPowerProperty,
	// 	EGameplayEffectAttributeCaptureSource::Source,
	// 	false
	// );
	// RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	/* Fast way of doing capture */
	RelevantAttributesToCapture.Add(GetPuraDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetPuraDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetPuraDamageCapture().DamageTakenDef);
}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// Get the GameplayEffectSpec which contains the information of the effect
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	// EffectSpec.GetContext().GetAbility();
	// EffectSpec.GetContext().GetSourceObject();
	// EffectSpec.GetContext().GetInstigator();
	// EffectSpec.GetContext().GetEffectCauser();
	
	// Get the evaluation parameters
	FAggregatorEvaluateParameters EvaluationParameters;
	// Set the source tags
	EvaluationParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	// Set the target tags
	EvaluationParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPuraDamageCapture().AttackPowerDef, EvaluationParameters, SourceAttackPower);
	// Debug::Print("SourceAttackPower", SourceAttackPower);
	float BaseDamage = 0.f;
	int32 UsingLightAttackComboCount = 0;
	int32 UsingHeavyAttackComboCount = 0;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if(TagMagnitude.Key.MatchesTagExact(PuraGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			// Debug::Print("BaseDamage", BaseDamage);
		}
		if(TagMagnitude.Key.MatchesTagExact(PuraGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsingLightAttackComboCount = TagMagnitude.Value;
		}
		if(TagMagnitude.Key.MatchesTagExact(PuraGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsingHeavyAttackComboCount = TagMagnitude.Value;
		}
	}
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPuraDamageCapture().DefensePowerDef, EvaluationParameters, TargetDefensePower);
	// Debug::Print("TargetDefensePower", TargetDefensePower);
	if(UsingLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsingLightAttackComboCount - 1) * 0.05 + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
	}
	if(UsingHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsingHeavyAttackComboCount * 0.15 + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
	}
	const float FinalDamageDone = BaseDamage * SourceAttackPower / TargetDefensePower;
	Debug::Print("FinalDamageDone", FinalDamageDone);
	if(FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetPuraDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone));
	}
}

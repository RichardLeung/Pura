// Fill out your copyright notice in the Description page of Project Settings.


#include "GEExecCalc_DamageTaken.h"
#include "Pura/AbilitySystem/PuraAttributeSet.h"
#include "Pura/Util/PuraDebugHelper.h"
#include "Pura/Util/PuraGameplayTags.h"

struct FPuraDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Attack);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Defense);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DamageTaken);

	FPuraDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPuraAttributeSet, Attack, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UPuraAttributeSet, Defense, Target, false);
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
	// FProperty* AttackProperty = FindFieldChecked<FProperty>(
	// 	UPuraAttributeSet::StaticClass(),
	// 	GET_MEMBER_NAME_CHECKED(UPuraAttributeSet, Attack)
	// );
	// FGameplayEffectAttributeCaptureDefinition AttackCaptureDefinition(
	// 	AttackProperty,
	// 	EGameplayEffectAttributeCaptureSource::Source,
	// 	false
	// );
	// RelevantAttributesToCapture.Add(AttackCaptureDefinition);

	/* Fast way of doing capture */
	RelevantAttributesToCapture.Add(GetPuraDamageCapture().AttackDef);
	RelevantAttributesToCapture.Add(GetPuraDamageCapture().DefenseDef);
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

	float SourceAttack = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPuraDamageCapture().AttackDef, EvaluationParameters,
	                                                           SourceAttack);
	// Debug::Print("SourceAttack", SourceAttack);
	float BaseDamage = SourceAttack;
	int32 UsingLightAttackComboCount = 0;
	int32 UsingHeavyAttackComboCount = 0;
	for (const TPair<FGameplayTag, float>& TagMagnitude : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagMagnitude.Key.MatchesTagExact(PuraGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagMagnitude.Value;
			// Debug::Print("BaseDamage", BaseDamage);
		}
		if (TagMagnitude.Key.MatchesTagExact(PuraGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			UsingLightAttackComboCount = TagMagnitude.Value;
		}
		if (TagMagnitude.Key.MatchesTagExact(PuraGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			UsingHeavyAttackComboCount = TagMagnitude.Value;
		}
	}
	float TargetDefense = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetPuraDamageCapture().DefenseDef, EvaluationParameters,
	                                                           TargetDefense);
	// Debug::Print("TargetDefense", TargetDefense);
	if (UsingLightAttackComboCount != 0)
	{
		const float DamageIncreasePercentLight = (UsingLightAttackComboCount - 1) * 0.05 + 1.f;
		BaseDamage *= DamageIncreasePercentLight;
	}
	if (UsingHeavyAttackComboCount != 0)
	{
		const float DamageIncreasePercentHeavy = UsingHeavyAttackComboCount * 0.15 + 1.f;
		BaseDamage *= DamageIncreasePercentHeavy;
	}
	const float FinalDamageDone = BaseDamage;

	// Debug::Print("FinalDamageDone", FinalDamageDone);
	if (FinalDamageDone > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(
				GetPuraDamageCapture().DamageTakenProperty,
				EGameplayModOp::Override,
				FinalDamageDone));
	}
}

#pragma once

UENUM()
enum class EPuraConfirmType : uint8
{
	Yes,
	No,
};

UENUM()
enum class EPuraValidType : uint8
{
	Valid,
	Invalid,
};

UENUM()
enum class EPuraSuccessType : uint8
{
	Success,
	Failure,
};

UENUM()
enum class EPuraCountDownActionInput : uint8
{
	Start,
	Cancel,
};

UENUM()
enum class EPuraCountDownActionOutput : uint8
{
	Updated,
	Completed,
	Cancelled,
};

UENUM(BlueprintType)
enum class EPuraGameDifficulty : uint8
{
	Easy,
	Normal,
	Hard,
	VeryHard,
};

UENUM(BlueprintType)
enum class EPuraInputMode : uint8
{
	GameOnly,
	UIOnly,
};

UENUM(BlueprintType)
enum class EPuraHeroStatus : uint8
{
	MaxHealth,
	MaxRageStar,
	MaxMana,
	Attack,
	Defense,
	MaxStamina,
	StaminaRecoveryRate,
	CriticalHitChance,
	CriticalHitDamage,
	DamageBonus,
	DamageReduction,
	Level,
	Experience,
	NextLevelExperience,
};

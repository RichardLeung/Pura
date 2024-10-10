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

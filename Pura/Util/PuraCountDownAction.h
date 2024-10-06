// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PuraEnumType.h"

class FPuraCountDownAction : public  FPendingLatentAction
{
public:
	FPuraCountDownAction(
		float InTotalCountDownTime,
		float InUpdateInterval,
		float& InOutRemainingTime,
		EPuraCountDownActionOutput& InCountDownOutput,
		const FLatentActionInfo& InLatentInfo) 
	:bNeedToCancel(false)
	,TotalCountDownTime(InTotalCountDownTime)
	,UpdateInterval(InUpdateInterval)
	,OutRemainingTime(InOutRemainingTime)
	,CountDownOutput(InCountDownOutput)
	,ExecutionFunction(InLatentInfo.ExecutionFunction)
	,OutputLink(InLatentInfo.Linkage)
	,CallbackTarget(InLatentInfo.CallbackTarget)
	,ElapsedInterval(0.f)
	,ElapsedTimeSinceStart(0.f)
	{
		
	}

	void CancelAction();

	
	void UpdateOperation(FLatentResponse& Response) override;

private:
	bool bNeedToCancel;
	float TotalCountDownTime;
	float UpdateInterval;
	float& OutRemainingTime;
	EPuraCountDownActionOutput& CountDownOutput;
	FName ExecutionFunction;
	int32 OutputLink;
	FWeakObjectPtr CallbackTarget;
	float ElapsedInterval;
	float ElapsedTimeSinceStart;
};

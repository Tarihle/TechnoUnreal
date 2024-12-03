// Fill out your copyright notice in the Description page of Project Settings.


#include "MegatronTask.h"
#include "GameplayTagsManager.h"

void UMegatronTask::Execute_Implementation()
{
	Status = EMegatronTaskStatus::IN_PROGRESS;
}

void UMegatronTask::Tick_Implementation(float DeltaSeconds)
{
	// Empty for parent class
}

void UMegatronTask::Abort()
{
	Status = EMegatronTaskStatus::ABORTED;
	OnTaskAbort.Broadcast();
}


EMegatronTaskStatus UMegatronTask::GetStatus() const
{
	return Status;
}

void UMegatronTask::Finish(bool bSuccess)
{
	if (EMegatronTaskStatus::IN_PROGRESS != Status)
		return;

	if (bSuccess)
	{
		Status = EMegatronTaskStatus::COMPLETED;
		OnTaskSuccess.Broadcast();
	}
	else
	{
		Status = EMegatronTaskStatus::FAILED;
		OnTaskFailure.Broadcast();
	}
}

EMegatronTaskStatus UMegatronTask::InternalTick(float DeltaSeconds)
{
	if (EMegatronTaskType::SINGLE_CALL == Type || EMegatronTaskStatus::IN_PROGRESS != Status)
		return Status;

	CurrentTickTime += DeltaSeconds;

	if (CurrentTickTime < Interval)
		return Status;

	CurrentTickTime = 0.f;
	Tick(DeltaSeconds);

	return Status;
}

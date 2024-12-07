// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MegatronTask.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTaskCompletedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTaskFailedSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTaskAbortedSignature);

UENUM(BlueprintType)
enum class EMegatronTaskStatus : uint8
{
	NOT_STARTED,
	IN_PROGRESS,
	COMPLETED,
	FAILED,
	ABORTED,
	IMPOSSIBLE
};

UENUM()
enum class EMegatronTaskType : uint8
{
	SINGLE_CALL,
	TICKED
};


/**
 *
 */
UCLASS(Blueprintable, Abstract)
class MEGATRONENEMIES_API UMegatronTask : public UObject
{
	GENERATED_BODY()

	friend class UBodyPart;

public:

	UFUNCTION(BlueprintPure)
	bool CanExecute() const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Execute();

	UFUNCTION(BlueprintImplementableEvent)
	void Tick(float DeltaSeconds);

	UFUNCTION(BlueprintCallable)
	EMegatronTaskStatus GetStatus() const;

	UFUNCTION(BlueprintCallable)
	void Abort();

	UFUNCTION(BlueprintCallable)
	void Finish(bool bSuccess);

private:

	EMegatronTaskStatus InternalTick(float DeltaSeconds);

public:

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FTaskCompletedSignature		OnTaskSuccess;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FTaskAbortedSignature		OnTaskAbort;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FTaskFailedSignature		OnTaskFailure;

protected:

	// Interval between each Tick call
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float					TickInterval = -1.f;

	// Cooldown before CanExecute function returns true
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float					ExecuteCooldown = 1.f;

private:

	float					CurrentExecuteCooldown = 0.f;
	float					CurrentTickTime = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	EMegatronTaskType		Type = EMegatronTaskType::TICKED;

	EMegatronTaskStatus		Status = EMegatronTaskStatus::NOT_STARTED;

};

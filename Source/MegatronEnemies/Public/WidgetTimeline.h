// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Components/TimelineComponent.h"
#include "Tickable.h"
#include "WidgetTimeline.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTimelineOutputPin);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTimelineOutputPinFloat, float, Value);


UCLASS(BlueprintType, meta=(ExposedAsyncProxy = AsyncAction))
class MEGATRONENEMIES_API UWidgetTimeline : public UBlueprintAsyncActionBase, public FTickableGameObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Widget Timeline")
	static UWidgetTimeline* WidgetTimeline(UCurveFloat* Curve, float Duration);

	UFUNCTION(BlueprintCallable, Category = "Widget Timeline")
	void Stop();

	UFUNCTION(BlueprintCallable, Category = "Widget Timeline")
	void Reverse();

	UFUNCTION(BlueprintCallable, Category = "Widget Timeline")
	void ReverseFromEnd();
	

	UPROPERTY(BlueprintAssignable, Category = "Widget Timeline")
	FTimelineOutputPinFloat Update;

	UPROPERTY(BlueprintAssignable, Category = "Widget Timeline")
	FTimelineOutputPin Finished;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Timeline")
	float CurveValue = 0.0f;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Timeline")
	float TimelineDuration = 1.0f;

private:
	FTimeline CurveTimeline;

	UPROPERTY()
	UCurveFloat* CurveFloat;


	virtual void Activate() override;

	virtual void Tick(float DeltaTime) override;

	virtual ETickableTickType GetTickableTickType() const override
	{
		return ETickableTickType::Always;
	}

	virtual TStatId GetStatId() const override
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(FMyTickableThing, STATGROUP_Tickables);
	}
	virtual bool IsTickableWhenPaused() const override
	{
		return true;
	}
	virtual bool IsTickableInEditor() const override
	{
		return false;
	}

	uint32 LastFrameNumberWeTicked = INDEX_NONE;


	UFUNCTION()
	void OnUpdate(float Value);

	UFUNCTION()
	void OnFinished();
};

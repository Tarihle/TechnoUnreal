// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetTimeline.h"
#include "Components/TimelineComponent.h"

UWidgetTimeline* UWidgetTimeline::WidgetTimeline(UCurveFloat* Curve, float const Duration)
{
	UWidgetTimeline* BlueprintNode = NewObject<UWidgetTimeline>();
	BlueprintNode->CurveFloat = Curve;
	BlueprintNode->TimelineDuration = Duration;
	return BlueprintNode;
}

void UWidgetTimeline::Stop()
{
	CurveTimeline.Stop();
	SetReadyToDestroy();
}

void UWidgetTimeline::Reverse()
{
	CurveTimeline.Reverse();
}

void UWidgetTimeline::ReverseFromEnd()
{
	CurveTimeline.ReverseFromEnd();
}

void UWidgetTimeline::Activate()
{
	if (CurveFloat == nullptr) return;

	FOnTimelineFloat TimelineUpdate;
	FOnTimelineEvent TimelineFinished;
	TimelineFinished.BindDynamic(this, &ThisClass::OnFinished);
	TimelineUpdate.BindDynamic(this, &ThisClass::OnUpdate);
	CurveTimeline.AddInterpFloat(CurveFloat, TimelineUpdate);

	CurveTimeline.AddEvent(CurveTimeline.GetTimelineLength(), TimelineFinished);

	CurveTimeline.SetPlayRate(1.0f / TimelineDuration);

	CurveTimeline.PlayFromStart();
}

void UWidgetTimeline::Tick(float DeltaTime)
{
	if (LastFrameNumberWeTicked == GFrameCounter) return;

	CurveTimeline.TickTimeline(DeltaTime);

	LastFrameNumberWeTicked = GFrameCounter;
}

void UWidgetTimeline::OnUpdate(float const Value)
{
	CurveValue = FMath::Lerp(0.0f, 1.0f, Value);
	Update.Broadcast(CurveValue);
}

void UWidgetTimeline::OnFinished()
{
	Finished.Broadcast();

	SetReadyToDestroy();
}
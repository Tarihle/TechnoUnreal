// Fill out your copyright notice in the Description page of Project Settings.


#include "BodyPart.h"
#include "MegatronTask.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/Class.h"

void UBodyPart::BeginPlay()
{
	Super::BeginPlay();
	for (auto& ActionTuple : ActionMap)
	{
		ActionTuple.Value.Index =
		Actions.Add(NewObject<UMegatronTask>(this, ActionTuple.Value.Class));
	}
}


UBodyPart::UBodyPart()
{
}

UMegatronTask* UBodyPart::GetTask(FGameplayTag Tag)
{

	if (Actions.IsEmpty())
	{
			UE_LOG(LogTemp, Error,
				   TEXT("%s action array is empty. GetTask may have been called before this object's BeginPlay sequence.\
Ignore this error if you are compiling a Blueprint"),
				   UKismetSystemLibrary::GetDisplayName(this).GetCharArray().GetData()
			);

			return nullptr;
	}

	else if (ActionMap.Contains(Tag))
		return Actions[ActionMap.Find(Tag)->Index];

	else return nullptr;
}

void UBodyPart::InitializeComponent()
{
	Super::InitializeComponent();
}


bool UBodyPart::IsLocomotion(UBodyPart* Part)
{
	return Part->Type == EBodyPartType::LOCOMOTION;
}

bool UBodyPart::IsConnector(UBodyPart* Part)
{
	return Part->Type == EBodyPartType::CONNECTOR;
}

void UBodyPart::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	for (UMegatronTask* Task : Actions)
		Task->InternalTick(DeltaTime);
}

bool UBodyPart::IsInteraction(UBodyPart* Part)
{
	return Part->Type == EBodyPartType::INTERACTION;
}

bool UBodyPart::IsPerception(UBodyPart* Part)
{
	return Part->Type == EBodyPartType::PERCEPTION;
}

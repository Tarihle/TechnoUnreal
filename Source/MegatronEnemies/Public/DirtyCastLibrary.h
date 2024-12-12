// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "DirtyCastLibrary.generated.h"

/**
 * 
 */
UCLASS()
class MEGATRONENEMIES_API UDirtyCastLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, meta=(DisplayName = "Cast Class To Class", DeterminesOutputType = "Class"), Category="Utilities")
	static UClass* Conv_ClassToClass(UClass* TargetClass, bool& bSucceed ,TSubclassOf<UObject> Class);
	
};

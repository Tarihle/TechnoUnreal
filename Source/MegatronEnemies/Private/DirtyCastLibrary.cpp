// Fill out your copyright notice in the Description page of Project Settings.


#include "DirtyCastLibrary.h"

UClass* UDirtyCastLibrary::Conv_ClassToClass(UClass* TargetClass, bool& bSucceed, TSubclassOf<UObject> Class)
{
	UClass* CastedClass = Cast<UClass>(TargetClass->GetDefaultObject());
	bSucceed = IsValid(CastedClass);
	return CastedClass;
}

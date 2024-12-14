// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EObject.h"
#include "Macro/EMacro.h"


void UEObject::BeginDestroy()
{
	UE_LOG(LogTemp, Warning, TEXT("UObject %s is being destroyed"), *GetName());
	Super::BeginDestroy();
}

EARBITRARY_IMPLEMENTATION(UEObject)
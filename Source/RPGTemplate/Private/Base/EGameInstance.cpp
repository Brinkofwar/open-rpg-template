// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EGameInstance.h"
#include "Macro/EMacro.h"

void UEGameInstance::Init()
{
	Super::Init();
	OnInitialized();
}

EARBITRARY_IMPLEMENTATION(UEGameInstance)
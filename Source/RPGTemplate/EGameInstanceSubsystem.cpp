// Fill out your copyright notice in the Description page of Project Settings.


#include "EGameInstanceSubsystem.h"

bool UEGameInstanceSubsystem::ShouldCreateSubsystem(UObject* object) const {
	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(object)) {
		return true;
	}
	return false;
}

void UEGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void UEGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

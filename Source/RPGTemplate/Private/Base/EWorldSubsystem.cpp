// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/EWorldSubsystem.h"

bool UEWorldSubsystem::ShouldCreateSubsystem(UObject* object) const
{

	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(object)) {
		return true;
	}
	return false;

}

void UEWorldSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnInitialized();
}

void UEWorldSubsystem::Deinitialize()
{
	Super::Deinitialize();
	OnDeinitialized();
}
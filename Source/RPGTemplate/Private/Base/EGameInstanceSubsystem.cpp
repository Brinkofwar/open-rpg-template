// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/EGameInstanceSubsystem.h"

bool UEGameInstanceSubsystem::ShouldCreateSubsystem(UObject* object) const
{

	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(object)) {
		return true;
	}
	return false;

}

/*
* Since the Game Instance Subsystem doesnt interact with the world.
*/
UWorld* UEGameInstanceSubsystem::GetWorld() const
{
	return nullptr;
}

void UEGameInstanceSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	OnInitialized();
}

void UEGameInstanceSubsystem::Deinitialize()
{
	Super::Deinitialize();
	OnDeinitialized();
}
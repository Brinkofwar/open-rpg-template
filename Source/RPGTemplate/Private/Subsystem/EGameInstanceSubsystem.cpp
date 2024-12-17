// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystem/EGameInstanceSubsystem.h"

bool UEGameInstanceSubsystem::ShouldCreateSubsystem(UObject* object) const
{

	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(object)) {
		return true;
	}
	return false;

}

UEGameInstanceSubsystem* UEGameInstanceSubsystem::GetSubsystem(TSubclassOf<UEGameInstanceSubsystem> SubsystemClass) const
{
	if (const UGameInstance* GameInstance = GetGameInstance())
	{
	
		UGameInstanceSubsystem* subsystem = GameInstance->GetSubsystemBase(SubsystemClass);
		if (!subsystem) {
			return nullptr;
		}

		return CastChecked<UEGameInstanceSubsystem>(subsystem);

	}

	return nullptr;
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
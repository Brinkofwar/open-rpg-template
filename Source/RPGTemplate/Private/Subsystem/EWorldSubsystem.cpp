// Fill out your copyright notice in the Description page of Project Settings.

#include "Subsystem/EWorldSubsystem.h"

bool UEWorldSubsystem::ShouldCreateSubsystem(UObject* object) const
{

	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(object)) {
		return true;
	}
	return false;

}

ULocalPlayer* UEWorldSubsystem::GetLocalPlayer() const
{

	ULocalPlayer* player = GetWorld()->GetFirstLocalPlayerFromController();
	if (player) {
		return player;
	}
	return nullptr;

}

APlayerController* UEWorldSubsystem::GetLocalPlayerController() const
{
	ULocalPlayer* player = GetLocalPlayer();

	if (player && GetWorld()) {

		APlayerController* controller = player->GetPlayerController(GetWorld());

		if (controller) {
			return controller;
		}

		return nullptr;

	}

	return nullptr;

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
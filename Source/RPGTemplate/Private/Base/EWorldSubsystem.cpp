// Fill out your copyright notice in the Description page of Project Settings.

#include "Base/EWorldSubsystem.h"
#include <Engine/StreamableManager.h>

bool UEWorldSubsystem::ShouldCreateSubsystem(UObject* object) const
{

	if (this->GetClass()->IsInBlueprint() && Super::ShouldCreateSubsystem(object)) {
		return true;
	}
	return false;

}

void UEWorldSubsystem::AsyncLoadAsset(TSoftObjectPtr<UObject> Object)
{

	FSoftObjectPath path = Object.ToSoftObjectPath();
	FStreamableManager streamableManager;

	streamableManager.RequestAsyncLoad(path, FStreamableDelegate::CreateLambda([this, path] {
		UObject* loadedAsset = path.ResolveObject();
		if (!loadedAsset)
		{
			UE_LOG(LogTemp, Warning, TEXT("Failed to load asset: %s"), *path.ToString());
			return;
		}
		OnAssetLoaded.Broadcast(loadedAsset);
		}), 0, false);

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
// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/AsyncAssetLoader.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

UAsyncAssetLoader* UAsyncAssetLoader::AsyncLoadAsset(TSoftObjectPtr<UObject> Asset)
{

	UAsyncAssetLoader* task = NewObject<UAsyncAssetLoader>();
	task->AssetToLoad = Asset;

	if (Asset.IsNull())
	{
		task->OnAssetLoaded.Broadcast(nullptr);
		task->SetReadyToDestroy();
		task->MarkAsGarbage();
		return task;
	}

	UAssetManager& assetManager = UAssetManager::Get();
	task->AssetHandle = assetManager.GetStreamableManager().RequestAsyncLoad(
		Asset.ToSoftObjectPath(),
		FStreamableDelegate::CreateUObject(task, &UAsyncAssetLoader::OnAssetLoadedInternally),
		FStreamableManager::AsyncLoadHighPriority
	);

	return task;

}


void UAsyncAssetLoader::OnAssetLoadedInternally()
{
	UObject* loadedAsset = AssetToLoad.Get();

	OnAssetLoaded.Broadcast(loadedAsset);

	SetReadyToDestroy();
	MarkAsGarbage();

}
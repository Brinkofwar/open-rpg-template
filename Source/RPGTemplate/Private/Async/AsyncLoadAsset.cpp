// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncLoadAsset.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

UAsyncLoadAsset* UAsyncLoadAsset::Start(TSoftObjectPtr<UObject> Asset)
{

	UAsyncLoadAsset* task = NewObject<UAsyncLoadAsset>();
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
		FStreamableDelegate::CreateUObject(task, &UAsyncLoadAsset::OnAssetLoadedInternally),
		FStreamableManager::AsyncLoadHighPriority
	);

	return task;

}

void UAsyncLoadAsset::OnAssetLoadedInternally()
{

	UObject* loadedAsset = AssetToLoad.Get();

	OnAssetLoaded.Broadcast(loadedAsset);

	SetReadyToDestroy();
	MarkAsGarbage();

}
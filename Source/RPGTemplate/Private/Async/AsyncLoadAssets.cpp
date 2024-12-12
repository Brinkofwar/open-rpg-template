// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncLoadAssets.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"


UAsyncLoadAssets* UAsyncLoadAssets::LoadAssets(const TArray<TSoftObjectPtr<UObject>>& Assets)
{
    UAsyncLoadAssets* task = NewObject<UAsyncLoadAssets>();
    task->AssetsToLoad = Assets;
    return task;
}

void UAsyncLoadAssets::Activate()
{
    if (AssetsToLoad.Num() == 0)
    {
        OnAllAssetsLoaded.Broadcast();
        EndTask();
        return;
    }

    PendingAssets = AssetsToLoad.Num();

    for (const auto& asset : AssetsToLoad)
    {
        LoadAsset(asset);
    }
}

void UAsyncLoadAssets::LoadAsset(const TSoftObjectPtr<UObject>& SoftObject)
{
    if (SoftObject.IsNull())
    {
        if (--PendingAssets <= 0)
        {
            OnAllAssetsLoaded.Broadcast();
            EndTask();
        }
        return;
    }

    if (UAssetManager* AssetManager = UAssetManager::GetIfInitialized())
    {
        AssetManager->GetStreamableManager().RequestAsyncLoad(
            SoftObject.ToSoftObjectPath(),
            FStreamableDelegate::CreateWeakLambda(this, [this, SoftObject]()
                {

                    UObject* loadedAsset = SoftObject.Get();

                    OnAnyAssetLoaded.Broadcast(loadedAsset);

                    if (--PendingAssets <= 0)
                    {
                        OnAllAssetsLoaded.Broadcast();
                        EndTask();
                    }

                }
            )
        );
    }
}

void UAsyncLoadAssets::EndTask()
{
    if (IsValid(this))
    {
        SetReadyToDestroy();
    }
}
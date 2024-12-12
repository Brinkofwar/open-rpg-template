// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncLoadMappedAssets.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"


UAsyncLoadMappedAssets* UAsyncLoadMappedAssets::LoadAssets(const TMap<FName, TSoftObjectPtr<UObject>>& Assets)
{
    UAsyncLoadMappedAssets* task = NewObject<UAsyncLoadMappedAssets>();
    task->AssetsToLoad = Assets;
    return task;
}

void UAsyncLoadMappedAssets::Activate()
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
        LoadAsset(asset.Key, asset.Value);
    }
}

void UAsyncLoadMappedAssets::LoadAsset(const FName& AssetName, const TSoftObjectPtr<UObject>& SoftObject)
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
            FStreamableDelegate::CreateWeakLambda(this, [this, AssetName, SoftObject]()
                {

                    UObject* loadedAsset = SoftObject.Get();

                    OnAnyAssetLoaded.Broadcast(AssetName, loadedAsset);

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

void UAsyncLoadMappedAssets::EndTask()
{
    if (IsValid(this))
    {
        SetReadyToDestroy();
    }
}
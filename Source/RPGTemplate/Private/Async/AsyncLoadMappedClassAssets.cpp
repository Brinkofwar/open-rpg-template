// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncLoadMappedClassAssets.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"

UAsyncLoadMappedClassAssets* UAsyncLoadMappedClassAssets::LoadAssets(const TMap<FName, TSoftClassPtr<UObject>>& Assets)
{
    UAsyncLoadMappedClassAssets* task = NewObject<UAsyncLoadMappedClassAssets>();
    task->AssetsToLoad = Assets;
    return task;
}

void UAsyncLoadMappedClassAssets::Activate()
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

void UAsyncLoadMappedClassAssets::LoadAsset(const FName& AssetName, const TSoftClassPtr<UObject>& SoftClass)
{
    if (!SoftClass.IsValid())
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
            SoftClass.ToSoftObjectPath(),
            FStreamableDelegate::CreateWeakLambda(this, [this, AssetName, SoftClass]()
                {
                    UClass* loadedAsset = SoftClass.Get();

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

void UAsyncLoadMappedClassAssets::EndTask()
{
    if (IsValid(this))
    {
        SetReadyToDestroy();
    }
}
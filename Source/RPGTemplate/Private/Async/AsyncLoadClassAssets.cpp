// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncLoadClassAssets.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Library/UtilityLibrary.h"

UAsyncLoadClassAssets* UAsyncLoadClassAssets::LoadAssets(const TArray<TSoftClassPtr<UObject>>& Assets)
{
    UAsyncLoadClassAssets* task = NewObject<UAsyncLoadClassAssets>();
    task->AssetsToLoad = Assets;
    return task;
}

void UAsyncLoadClassAssets::Activate()
{
    if (AssetsToLoad.Num() == 0)
    {
        OnAllAssetsLoaded.Broadcast();
        EndTask();
        return;
    }

    PendingAssets = AssetsToLoad.Num();

    for (auto& asset : AssetsToLoad)
    {
        LoadAsset(asset);
    }
}

void UAsyncLoadClassAssets::LoadAsset(const TSoftClassPtr<UObject>& SoftClass)
{

    if (SoftClass.IsNull())
    {
        if (--PendingAssets <= 0)
        {
            OnAllAssetsLoaded.Broadcast();
            EndTask();
        }
        return;
    }
    
    if (UAssetManager* AssetManager = UAssetManager::GetIfValid())
    {
        AssetManager->GetStreamableManager().RequestAsyncLoad(
            SoftClass.ToSoftObjectPath(),
            FStreamableDelegate::CreateWeakLambda(this, [this, SoftClass]()
                {

                    UClass* loadedAsset = SoftClass.Get();

                    OnAnyAssetLoaded.Broadcast(loadedAsset);

                    if (--PendingAssets <= 0)
                    {
                        OnAllAssetsLoaded.Broadcast();
                    }

                }
            )
        );
    }
}

void UAsyncLoadClassAssets::EndTask()
{
    if (IsValid(this))
    {
        SetReadyToDestroy();
    }
}
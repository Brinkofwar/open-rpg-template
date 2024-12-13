// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncLoadAssets.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"


UAsyncLoadAssets* UAsyncLoadAssets::Start(const TArray<TSoftObjectPtr<UObject>>& Assets)
{
    UAsyncLoadAssets* task = NewObject<UAsyncLoadAssets>();
    task->AssetsToLoad = Assets;

    for (int32 i = 0, len = Assets.Num(); i < len; ++i)
    {
        task->AssetIndexMap.Add(Assets[i], i);
    }

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

    LoadAsset(AssetsToLoad);
}

void UAsyncLoadAssets::LoadAsset(const TArray<TSoftObjectPtr<UObject>>& SoftObjects)
{

    if (UAssetManager* assetManager = UAssetManager::GetIfInitialized())
    {

        TArray<FSoftObjectPath> assetPaths;
        for (const auto& Asset : SoftObjects)
        {
            if (!Asset.IsNull())
            {
                assetPaths.Add(Asset.ToSoftObjectPath());
            }
        }

        if (assetPaths.Num() > 0)
        {

            assetManager->GetStreamableManager().RequestAsyncLoad(
                assetPaths,
                FStreamableDelegate::CreateWeakLambda(this, [this, SoftObjects]()
                    {

                        for (int32 i = 0; i < SoftObjects.Num(); ++i)
                        {
                            UObject* loadedAsset = SoftObjects[i].Get();
                            int32 assetIndex = AssetIndexMap.FindChecked(SoftObjects[i]);

                            OnAnyAssetLoaded.Broadcast(loadedAsset, assetIndex);
                        }
                        
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

}

void UAsyncLoadAssets::EndTask()
{
    if (IsValid(this))
    {
        SetReadyToDestroy();
        MarkAsGarbage();
    }
}
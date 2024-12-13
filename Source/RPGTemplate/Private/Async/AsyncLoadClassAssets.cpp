// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncLoadClassAssets.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Library/UtilityLibrary.h"

UAsyncLoadClassAssets* UAsyncLoadClassAssets::Start(const TArray<TSoftClassPtr<UObject>>& Assets)
{
    UAsyncLoadClassAssets* task = NewObject<UAsyncLoadClassAssets>();
    task->AssetsToLoad = Assets;

    for (int32 i = 0, len = Assets.Num(); i < len; ++i)
    {
        task->AssetIndexMap.Add(Assets[i], i);
    }

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

    LoadAsset(AssetsToLoad);
}

void UAsyncLoadClassAssets::LoadAsset(const TArray<TSoftClassPtr<UObject>>& SoftClasses)
{

    if (UAssetManager* assetManager = UAssetManager::GetIfInitialized())
    {

        TArray<FSoftObjectPath> assetPaths;
        for (const auto& Asset : SoftClasses)
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
                FStreamableDelegate::CreateWeakLambda(this, [this, SoftClasses]()
                    {

                        for (int32 i = 0; i < SoftClasses.Num(); ++i)
                        {
                            UClass* loadedAsset = SoftClasses[i].Get();
                            int32 assetIndex = AssetIndexMap.FindChecked(SoftClasses[i]);

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

void UAsyncLoadClassAssets::EndTask()
{
    if (IsValid(this))
    {
        SetReadyToDestroy();
        MarkAsGarbage();
    }
}
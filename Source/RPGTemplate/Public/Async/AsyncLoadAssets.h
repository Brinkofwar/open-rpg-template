// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncLoadAssets.generated.h"


/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UAsyncLoadAssets : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, DisplayName = "Async Load Assets", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncLoadAssets* Start(const TArray<TSoftObjectPtr<UObject>>& Assets);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyAssetLoaded, UObject*, Asset, int32, Index);
	UPROPERTY(BlueprintAssignable, DisplayName = "Loaded")
	FOnAnyAssetLoaded OnAnyAssetLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllAssetsLoaded);
	UPROPERTY(BlueprintAssignable, DisplayName = "Completed")
	FOnAllAssetsLoaded OnAllAssetsLoaded;

private:

	void EndTask();

    void LoadAsset(const TArray<TSoftObjectPtr<UObject>>& SoftObjects);

	TArray<TSoftObjectPtr<UObject>> AssetsToLoad;
	TMap<TSoftObjectPtr<UObject>, int32> AssetIndexMap;

    int32 PendingAssets = 0;

};

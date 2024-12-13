// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncLoadClassAssets.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UAsyncLoadClassAssets : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Async Load Class Assets", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncLoadClassAssets* Start(const TArray<TSoftClassPtr<UObject>>& Assets);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyAssetLoaded, UClass*, Asset, int, Index);
	UPROPERTY(BlueprintAssignable, DisplayName = "Loaded")
	FOnAnyAssetLoaded OnAnyAssetLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllAssetsLoaded);
	UPROPERTY(BlueprintAssignable, DisplayName = "Completed")
	FOnAllAssetsLoaded OnAllAssetsLoaded;


private:

	void EndTask();

	void LoadAsset(const TArray<TSoftClassPtr<UObject>>& SoftClasses);

	TArray<TSoftClassPtr<UObject>> AssetsToLoad;
	TMap<TSoftClassPtr<UObject>, int32> AssetIndexMap;

	int32 PendingAssets = 0;
	
};

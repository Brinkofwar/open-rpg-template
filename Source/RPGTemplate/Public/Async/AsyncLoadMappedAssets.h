// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncLoadMappedAssets.generated.h"


/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UAsyncLoadMappedAssets : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, DisplayName = "Async Load Mapped Assets", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncLoadMappedAssets* Start(const TMap<FName, TSoftObjectPtr<UObject>>& Assets);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyAssetLoaded, FName, AssetName, UObject*, Asset);
	UPROPERTY(BlueprintAssignable, DisplayName = "Loaded")
	FOnAnyAssetLoaded OnAnyAssetLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllAssetsLoaded);
	UPROPERTY(BlueprintAssignable, DisplayName = "Completed")
	FOnAllAssetsLoaded OnAllAssetsLoaded;

private:

	void EndTask();

    void LoadAsset(const FName& AssetName, const TSoftObjectPtr<UObject>& SoftObject);

	TMap<FName, TSoftObjectPtr<UObject>> AssetsToLoad;

    int32 PendingAssets = 0;

};

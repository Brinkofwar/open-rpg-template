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
	static UAsyncLoadAssets* LoadAssets(const TArray<TSoftObjectPtr<UObject>>& Assets);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyAssetLoaded, UObject*, Asset);
	UPROPERTY(BlueprintAssignable)
	FOnAnyAssetLoaded OnAnyAssetLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllAssetsLoaded);
	UPROPERTY(BlueprintAssignable)
	FOnAllAssetsLoaded OnAllAssetsLoaded;

private:

	void EndTask();

    void LoadAsset(const TSoftObjectPtr<UObject>& SoftObject);

	TArray<TSoftObjectPtr<UObject>> AssetsToLoad;

    int32 PendingAssets = 0;

};

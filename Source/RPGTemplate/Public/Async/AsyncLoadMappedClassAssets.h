// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncLoadMappedClassAssets.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UAsyncLoadMappedClassAssets : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Async Load Mapped Class Assets", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncLoadMappedClassAssets* LoadAssets(const TMap<FName, TSoftClassPtr<UObject>>& Assets);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAnyAssetLoaded, FName, AssetName, UClass*, Asset);
	UPROPERTY(BlueprintAssignable)
	FOnAnyAssetLoaded OnAnyAssetLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllAssetsLoaded);
	UPROPERTY(BlueprintAssignable)
	FOnAllAssetsLoaded OnAllAssetsLoaded;

private:

	void EndTask();

	void LoadAsset(const FName& AssetName, const TSoftClassPtr<UObject>& SoftClass);

	TMap<FName, TSoftClassPtr<UObject>> AssetsToLoad;

	int32 PendingAssets = 0;
	
};

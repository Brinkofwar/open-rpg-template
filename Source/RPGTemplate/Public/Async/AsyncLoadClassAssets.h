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
	static UAsyncLoadClassAssets* LoadAssets(const TArray<TSoftClassPtr<UObject>>& Assets);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnyAssetLoaded, UClass*, Asset);
	UPROPERTY(BlueprintAssignable)
	FOnAnyAssetLoaded OnAnyAssetLoaded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAllAssetsLoaded);
	UPROPERTY(BlueprintAssignable)
	FOnAllAssetsLoaded OnAllAssetsLoaded;

private:

	void EndTask();

	void LoadAsset(const TSoftClassPtr<UObject>& SoftClass);

	TArray<TSoftClassPtr<UObject>> AssetsToLoad;

	int32 PendingAssets = 0;
	
};

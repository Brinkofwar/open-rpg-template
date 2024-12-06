// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Engine/StreamableManager.h"
#include "AsyncAssetLoader.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAssetLoaded, UObject*, LoadedAsset);

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UAsyncAssetLoader : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Asset Loading", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncAssetLoader* AsyncLoadAsset(TSoftObjectPtr<UObject> Asset);


	UPROPERTY(BlueprintAssignable)
	FOnAssetLoaded OnAssetLoaded;

protected:

	void OnAssetLoadedInternally();

	TSoftObjectPtr<UObject> AssetToLoad;

	TSharedPtr<FStreamableHandle> AssetHandle;

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Engine/StreamableManager.h"
#include "AsyncLoadAsset.generated.h"



/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UAsyncLoadAsset : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Async Load Asset", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncLoadAsset* Start(TSoftObjectPtr<UObject> Asset);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAssetLoaded, UObject*, Asset);
	UPROPERTY(BlueprintAssignable, DisplayName = "Loaded")
	FOnAssetLoaded OnAssetLoaded;

protected:

	void OnAssetLoadedInternally();

	TSoftObjectPtr<UObject> AssetToLoad;

	TSharedPtr<FStreamableHandle> AssetHandle;

};

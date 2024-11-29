// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EGameInstanceSubsystem.generated.h"

/**
 *
 */
UCLASS(Blueprintable)
class RPGTEMPLATE_API UEGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Enhanced Game Instance Subsystem")
	void Begin();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced Game Instance Subsystem")
	void OnInitialized();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced Game Instance Subsystem")
	void OnDeinitialized();

	UFUNCTION(BlueprintCallable, Category = "Enhanced Game Instance Subsystem")
	void AsyncLoadAsset(TSoftObjectPtr<UObject> Object);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAssetLoaded, UObject*, LoadedAsset);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced Game Instance Subsystem|Event Dispatcher")
	FOnAssetLoaded OnAssetLoaded;

#pragma region Arbitrary

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Enhanced Game Instance Subsystem")
	void ArbitraryChannel(FGameplayTag ChannelID, FInstancedStruct Parameters, FGameplayTag& Out_ChannelID, FInstancedStruct& Out_Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced Game Instance Subsystem")
	void OnArbitraryRequested(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced Game Instance Subsystem")
	void OnArbitraryResponded(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Enhanced Game Instance Subsystem|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced Game Instance Subsystem|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

#pragma endregion Arbitrary

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* object) const override;

};

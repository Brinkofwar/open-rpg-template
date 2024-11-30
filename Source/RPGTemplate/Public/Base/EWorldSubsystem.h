// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RPGTEMPLATE_API UEWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Enhanced World Subsystem")
	void Begin();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced World Subsystem")
	void OnInitialized();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced World Subsystem")
	void OnDeinitialized();

	UFUNCTION(BlueprintCallable, Category = "Enhanced World Subsystem")
	void AsyncLoadAsset(TSoftObjectPtr<UObject> Object);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAssetLoaded, UObject*, LoadedAsset);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced World Subsystem|Event Dispatcher")
	FOnAssetLoaded OnAssetLoaded;

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* object) const override;
	
};

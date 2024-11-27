// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* object) const override;

};

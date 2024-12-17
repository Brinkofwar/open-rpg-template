// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EGameInstanceSubsystem.generated.h"

/**
* UEGameInstanceSubsystem
* A subsystem for managing global game systems such as storage, inventory, and other persistent data.
* Game Instance Subsystems are not tied to a specific world, as they operate at the game instance,
* which persists across all worlds.
*/
UCLASS(Blueprintable, DisplayName = "Extended Game Instance Subsystem")
class RPGTEMPLATE_API UEGameInstanceSubsystem : public UGameInstanceSubsystem
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Extended Game Instance Subsystem")
	void PostInitialize();

	UFUNCTION(BlueprintImplementableEvent, Category = "Extended Game Instance Subsystem")
	void OnInitialized();

	UFUNCTION(BlueprintImplementableEvent, Category = "Extended Game Instance Subsystem")
	void OnDeinitialized();

	UFUNCTION(BlueprintCallable, Category = "Extended Game Instance Subsystem", meta = (DeterminesOutputType = "SubsystemClass"))
	UEGameInstanceSubsystem* GetSubsystem(TSubclassOf<UEGameInstanceSubsystem> SubsystemClass) const;

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* object) const override;
	virtual UWorld* GetWorld() const override;

};

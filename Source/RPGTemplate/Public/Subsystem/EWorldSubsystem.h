// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, DisplayName = "Extended World Subsystem")
class RPGTEMPLATE_API UEWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Extended World Subsystem")
	void PostInitialize();

	UFUNCTION(BlueprintImplementableEvent, Category = "Extended World Subsystem")
	void OnInitialized();

	UFUNCTION(BlueprintImplementableEvent, Category = "Extended World Subsystem")
	void OnDeinitialized();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Extended World Subsystem")
	ULocalPlayer* GetLocalPlayer() const;

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Extended World Subsystem")
	APlayerController* GetLocalPlayerController() const;

protected:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* object) const override;
	
};

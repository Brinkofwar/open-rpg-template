// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "EWorldSubsystem.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RPGTEMPLATE_API UEWorldSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced World Subsystem")
	void OnInitialized();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced World Subsystem")
	void OnDeinitialized();

protected:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	virtual bool ShouldCreateSubsystem(UObject* object) const override;
	
};

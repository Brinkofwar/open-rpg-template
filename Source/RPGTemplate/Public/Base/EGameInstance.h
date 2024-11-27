// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "EGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UEGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialized();
};

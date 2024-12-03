// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InstancedStruct.h"
#include "EUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UEUserWidget : public UUserWidget
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced User Widget", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;

};

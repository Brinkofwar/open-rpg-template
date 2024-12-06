// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "BEGameplayModifierEvaluatedData.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FBEGameplayModifierEvaluatedData
{

	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayAttribute Attribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EGameplayModOp::Type> ModifierOp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Magnitude;

};

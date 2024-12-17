// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/EAttributeSet.h"
#include "HealthAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UHealthAttributeSet : public UEAttributeSet
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, Health)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(UHealthAttributeSet, HealthMax)

	virtual void SetAttribute(FGameplayAttribute Attribute, float NewValue) override;
	virtual float GetAttribute(FGameplayAttribute Attribute) const override;
	
};

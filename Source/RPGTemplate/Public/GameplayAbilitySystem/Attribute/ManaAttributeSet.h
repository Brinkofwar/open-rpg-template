// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySystem/EAttributeSet.h"
#include "ManaAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UManaAttributeSet : public UEAttributeSet
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, Mana)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData ManaMax;
	ATTRIBUTE_ACCESSORS(UManaAttributeSet, ManaMax)

	virtual void SetAttribute(FGameplayAttribute Attribute, float NewValue) override;
	virtual float GetAttribute(FGameplayAttribute Attribute) const override;
	
};

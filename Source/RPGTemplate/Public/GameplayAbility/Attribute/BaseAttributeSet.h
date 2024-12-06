// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "BaseAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

#define SET_ATTRIBUTE(Name) \
	if(Attribute == Get##Name##Attribute()) { \
		Set##Name(NewValue); \
	}

#define GET_ATTRIBUTE(Name) \
	if(Attribute == Get##Name##Attribute()) { \
		value = Get##Name(); \
	}

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UBaseAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, Health)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData HealthMax;
	ATTRIBUTE_ACCESSORS(UBaseAttributeSet, HealthMax)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool AllowBlueprintExecution = false;

	UFUNCTION(BlueprintImplementableEvent)
	float OnPreAttributeChange(const FGameplayAttribute& Attribute, float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent)
	void OnPostGameplayEffectExecute(const FGameplayEffectSpec InEffectSpec, FBEGameplayModifierEvaluatedData InEvaluatedData, UAbilitySystemComponent* InTarget);

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

protected:

	UFUNCTION(BlueprintCallable)
	void SetAttribute(FGameplayAttribute Attribute, float NewValue);

	UFUNCTION(BlueprintCallable)
	float GetAttribute(FGameplayAttribute Attribute) const;
	
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName) \

#define SET_ATTRIBUTE(Name) \
	if(Attribute == Get##Name##Attribute()) { \
		Set##Name(NewValue); \
		return; \
	} \

#define GET_ATTRIBUTE(Name) \
	if(Attribute == Get##Name##Attribute()) { \
		return Get##Name(); \
	} \

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UEAttributeSet : public UAttributeSet
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced Attribute Set")
	const bool AllowBlueprintExecution();

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced Attribute Set")
	float OnPreAttributeChange(const FGameplayAttribute& Attribute, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced Attribute Set")
	bool OnPostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue);

	UFUNCTION(BlueprintImplementableEvent, Category = "Enhanced Attribute Set")
	bool OnPostGameplayEffectExecute(const FGameplayEffectSpec InEffectSpec, FBEGameplayModifierEvaluatedData InEvaluatedData, UAbilitySystemComponent* InTarget);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Attribute Set")
	virtual void SetAttribute(FGameplayAttribute Attribute, float NewValue);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Attribute Set")
	virtual float GetAttribute(FGameplayAttribute Attribute) const;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

};

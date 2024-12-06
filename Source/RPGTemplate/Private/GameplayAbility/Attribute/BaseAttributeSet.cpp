// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility/Attribute/BaseAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "DataType/Struct/BEGameplayModifierEvaluatedData.h"


void UBaseAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

	Super::PreAttributeChange(Attribute, NewValue);
	if (AllowBlueprintExecution) {
		NewValue = OnPreAttributeChange(Attribute, NewValue);
	}

}

void UBaseAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{

	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (AllowBlueprintExecution) {
		OnPostAttributeChange(Attribute, OldValue, NewValue);
	}

}

void UBaseAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	Super::PostGameplayEffectExecute(Data);

	if (AllowBlueprintExecution) {

		FBEGameplayModifierEvaluatedData evaluatedData;
		evaluatedData.Attribute = Data.EvaluatedData.Attribute;
		evaluatedData.Magnitude = Data.EvaluatedData.Magnitude;
		evaluatedData.ModifierOp = Data.EvaluatedData.ModifierOp;

		OnPostGameplayEffectExecute(Data.EffectSpec, evaluatedData, &Data.Target);

	}

}


void UBaseAttributeSet::SetAttribute(FGameplayAttribute Attribute, float NewValue)
{

	if (!Attribute.IsValid()) {
		return;
	}

	SET_ATTRIBUTE(Health);
	SET_ATTRIBUTE(HealthMax);

}


float UBaseAttributeSet::GetAttribute(FGameplayAttribute Attribute) const
{

	float value = 0.0f;

	if (!Attribute.IsValid()) {
		return value;
	}

	GET_ATTRIBUTE(Health);
	GET_ATTRIBUTE(HealthMax);

	return value;

}
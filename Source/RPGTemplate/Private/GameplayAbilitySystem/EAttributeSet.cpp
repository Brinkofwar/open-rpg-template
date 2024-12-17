// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/EAttributeSet.h"
#include "GameplayEffect.h"
#include "GameplayEffectExtension.h"
#include "DataType/Struct/BEGameplayModifierEvaluatedData.h"


void UEAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{

	Super::PreAttributeChange(Attribute, NewValue);
	if (AllowBlueprintExecution()) {
		NewValue = OnPreAttributeChange(Attribute, NewValue);
	}

}

void UEAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{

	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	if (AllowBlueprintExecution()) {
		OnPostAttributeChange(Attribute, OldValue, NewValue);
	}

}

void UEAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{

	Super::PostGameplayEffectExecute(Data);

	if (AllowBlueprintExecution()) {

		FBEGameplayModifierEvaluatedData evaluatedData;
		evaluatedData.Attribute = Data.EvaluatedData.Attribute;
		evaluatedData.Magnitude = Data.EvaluatedData.Magnitude;
		evaluatedData.ModifierOp = Data.EvaluatedData.ModifierOp;

		OnPostGameplayEffectExecute(Data.EffectSpec, evaluatedData, &Data.Target);

	}

}

void UEAttributeSet::SetAttribute(FGameplayAttribute Attribute, float NewValue)
{

	if (!Attribute.IsValid()) {
		return;
	}

}


float UEAttributeSet::GetAttribute(FGameplayAttribute Attribute) const
{

	if (!Attribute.IsValid()) {
		return 0.0f;
	}

	return 0.0f;

}
// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Attribute/HealthAttributeSet.h"

void UHealthAttributeSet::SetAttribute(FGameplayAttribute Attribute, float NewValue)
{

	Super::SetAttribute(Attribute, NewValue);

	SET_ATTRIBUTE(Health);
	SET_ATTRIBUTE(HealthMax);

}

float UHealthAttributeSet::GetAttribute(FGameplayAttribute Attribute) const
{

	float value = Super::GetAttribute(Attribute);

	GET_ATTRIBUTE(Health);
	GET_ATTRIBUTE(HealthMax);

	return value;

}

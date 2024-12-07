// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Attribute/ManaAttributeSet.h"

void UManaAttributeSet::SetAttribute(FGameplayAttribute Attribute, float NewValue)
{

	Super::SetAttribute(Attribute, NewValue);

	SET_ATTRIBUTE(Mana);
	SET_ATTRIBUTE(ManaMax);

}

float UManaAttributeSet::GetAttribute(FGameplayAttribute Attribute) const
{

	float value = Super::GetAttribute(Attribute);

	GET_ATTRIBUTE(Mana);
	GET_ATTRIBUTE(ManaMax);

	return value;

}

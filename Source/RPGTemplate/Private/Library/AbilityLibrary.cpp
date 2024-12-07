// Fill out your copyright notice in the Description page of Project Settings.

#include "Library/AbilityLibrary.h"
#include "GameplayAbilities/Public/Abilities/GameplayAbility.h"
#include "GameplayAbilities/Public/AbilitySystemComponent.h"

bool UAbilityLibrary::GetAbilitySpecByTag(const UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag Tag, FGameplayAbilitySpecHandle& AbilitySpecHandle)
{
	if (!AbilitySystemComponent) {
		return false;
	}

	TArray<FGameplayAbilitySpec> abilitySpecs = AbilitySystemComponent->GetActivatableAbilities();

	for (const FGameplayAbilitySpec& abilitySpec : abilitySpecs)
	{
		if (abilitySpec.Ability && abilitySpec.Ability->AbilityTags.HasTagExact(Tag)) {
			AbilitySpecHandle = abilitySpec.Handle;
			return true;
		}
	}

	return false;
}

bool UAbilityLibrary::GetAllAbilitySpecsByTag(const UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag Tag, TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles)
{
	if (!AbilitySystemComponent) {
		return false;
	}

	TArray<FGameplayAbilitySpec> abilitySpecs = AbilitySystemComponent->GetActivatableAbilities();

	for (const FGameplayAbilitySpec& abilitySpec : abilitySpecs)
	{
		if (abilitySpec.Ability && abilitySpec.Ability->AbilityTags.HasTagExact(Tag)) {
			AbilitySpecHandles.Add(abilitySpec.Handle);
		}
	}

	return true;
}


FGameplayTagContainer UAbilityLibrary::GetAbilityTags(const UGameplayAbility* Ability)
{
	if (!Ability) {
		return FGameplayTagContainer();
	}
	return Ability->AbilityTags;
}

bool UAbilityLibrary::HasAnyTags(const UGameplayAbility* Ability, const FGameplayTagContainer Tags)
{
	if (!Ability) {
		return false;
	}
	return Ability->AbilityTags.HasAny(Tags);
}

bool UAbilityLibrary::HasAnyExactTags(const UGameplayAbility* Ability, const FGameplayTagContainer Tags)
{
	if (!Ability) {
		return false;
	}
	return Ability->AbilityTags.HasAnyExact(Tags);
}

bool UAbilityLibrary::HasAllTags(const UGameplayAbility* Ability, const FGameplayTagContainer Tags)
{
	if (!Ability) {
		return false;
	}
	return Ability->AbilityTags.HasAll(Tags);
}

bool UAbilityLibrary::HasAllExactTags(const UGameplayAbility* Ability, const FGameplayTagContainer Tags)
{
	if (!Ability) {
		return false;
	}
	return Ability->AbilityTags.HasAllExact(Tags);
}


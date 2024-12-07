// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AbilityLibrary.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UAbilityLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "Ability Library")
	static bool GetAbilitySpecByTag(const UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag Tag, FGameplayAbilitySpecHandle& AbilitySpecHandle);

	UFUNCTION(BlueprintCallable, Category = "Ability Library")
	static bool GetAllAbilitySpecsByTag(const UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag Tag, TArray<FGameplayAbilitySpecHandle>& AbilitySpecHandles);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability Library")
	static FGameplayTagContainer GetAbilityTags(const UGameplayAbility* Ability);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability Library")
	static bool HasAnyTags(const UGameplayAbility* Ability, const FGameplayTagContainer Tags);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability Library")
	static bool HasAnyExactTags(const UGameplayAbility* Ability, const FGameplayTagContainer Tags);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability Library")
	static bool HasAllTags(const UGameplayAbility* Ability, const FGameplayTagContainer Tags);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Ability Library")
	static bool HasAllExactTags(const UGameplayAbility* Ability, const FGameplayTagContainer Tags);

};

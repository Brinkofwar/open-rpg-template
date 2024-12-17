// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "InstancedStruct.h"

#include "EAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, DisplayName = "Extended Ability System Component", ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class RPGTEMPLATE_API UEAbilitySystemComponent : public UAbilitySystemComponent
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Add Loose Gameplay Tags", Category = "Extended Ability System Component")
	void SAddLooseGameplayTags(FGameplayTagContainer Tags);
	void SAddLooseGameplayTags_Implementation(FGameplayTagContainer Tags);
	bool SAddLooseGameplayTags_Validate(FGameplayTagContainer Tags);

	UFUNCTION(NetMulticast, Reliable)
	void CAddLooseGameplayTags(FGameplayTagContainer Tags);
	void CAddLooseGameplayTags_Implementation(FGameplayTagContainer Tags);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Remove Loose Gameplay Tags", Category = "Extended Ability System Component")
	void SRemoveLooseGameplayTags(FGameplayTagContainer Tags);
	void SRemoveLooseGameplayTags_Implementation(FGameplayTagContainer Tags);
	bool SRemoveLooseGameplayTags_Validate(FGameplayTagContainer Tags);

	UFUNCTION(NetMulticast, Reliable)
	void CRemoveLooseGameplayTags(FGameplayTagContainer Tags);
	void CRemoveLooseGameplayTags_Implementation(FGameplayTagContainer Tags);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Send Gameplay Event", Category = "Extended Ability System Component")
	void SSendGameplayEvent(FGameplayTag EventTag, FGameplayEventData Payload);
	void SSendGameplayEvent_Implementation(FGameplayTag EventTag, FGameplayEventData Payload);
	bool SSendGameplayEvent_Validate(FGameplayTag EventTag, FGameplayEventData Payload);

	UFUNCTION(NetMulticast, Reliable)
	void CSendGameplayEvent(FGameplayTag EventTag, FGameplayEventData Payload);
	void CSendGameplayEvent_Implementation(FGameplayTag EventTag, FGameplayEventData Payload);

};

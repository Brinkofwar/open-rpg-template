// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/EAbilitySystemComponent.h"
#include "GameplayAbilities/Public/AbilitySystemBlueprintLibrary.h"


void UEAbilitySystemComponent::SAddLooseGameplayTags_Implementation(FGameplayTagContainer Tags)
{
	CAddLooseGameplayTags(Tags);
}
bool UEAbilitySystemComponent::SAddLooseGameplayTags_Validate(FGameplayTagContainer Tags)
{
	return Tags.IsValid();
}
void UEAbilitySystemComponent::CAddLooseGameplayTags_Implementation(FGameplayTagContainer Tags)
{
	UAbilitySystemBlueprintLibrary::AddLooseGameplayTags(this->GetOwnerActor(), Tags, true);
}


void UEAbilitySystemComponent::SRemoveLooseGameplayTags_Implementation(FGameplayTagContainer Tags)
{
	CRemoveLooseGameplayTags(Tags);
}
bool UEAbilitySystemComponent::SRemoveLooseGameplayTags_Validate(FGameplayTagContainer Tags)
{
	return Tags.IsValid();
}
void UEAbilitySystemComponent::CRemoveLooseGameplayTags_Implementation(FGameplayTagContainer Tags)
{
	UAbilitySystemBlueprintLibrary::RemoveLooseGameplayTags(this->GetOwnerActor(), Tags, true);
}


void UEAbilitySystemComponent::SSendGameplayEvent_Implementation(FGameplayTag EventTag, FGameplayEventData Payload)
{
	CSendGameplayEvent(EventTag, Payload);
}
bool UEAbilitySystemComponent::SSendGameplayEvent_Validate(FGameplayTag EventTag, FGameplayEventData Payload)
{
	return EventTag.IsValid() && this->GetOwnerActor();
}
void UEAbilitySystemComponent::CSendGameplayEvent_Implementation(FGameplayTag EventTag, FGameplayEventData Payload)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this->GetOwnerActor(), EventTag, Payload);
}
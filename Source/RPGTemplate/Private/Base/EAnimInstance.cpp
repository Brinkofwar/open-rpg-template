// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EAnimInstance.h"

void UEAnimInstance::OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}
void UEAnimInstance::OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}

bool UEAnimInstance::AddTag(FGameplayTag Tag)
{
	if (!GameplayTags.HasTag(Tag)) {
		GameplayTags.AddTag(Tag);
		OnTagAdded(Tag);
		OnTagAdd.Broadcast(Tag);
		return true;
	}
	return false;
}

bool UEAnimInstance::RemoveTag(FGameplayTag Tag)
{
	if (GameplayTags.RemoveTag(Tag)) {
		OnTagRemoved(Tag);
		OnTagRemove.Broadcast(Tag);
		return true;
	}
	return false;
}

bool UEAnimInstance::HasAnyTags(FGameplayTagContainer Tag, bool ExactMatch) const
{
	return (ExactMatch) ? GameplayTags.HasAnyExact(Tag) : GameplayTags.HasAny(Tag);
}

void UEAnimInstance::OnTagAdded_Implementation(FGameplayTag Tag) {}
void UEAnimInstance::OnTagRemoved_Implementation(FGameplayTag Tag) {}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EObject.h"

void UEObject::OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}
void UEObject::OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}

bool UEObject::AddTag(FGameplayTag Tag)
{
	if (!GameplayTags.HasTag(Tag)) {
		GameplayTags.AddTag(Tag);
		OnTagAdded(Tag);
		OnTagAdd.Broadcast(Tag);
		return true;
	}
	return false;
}

bool UEObject::RemoveTag(FGameplayTag Tag)
{
	if (GameplayTags.RemoveTag(Tag)) {
		OnTagRemoved(Tag);
		OnTagRemove.Broadcast(Tag);
		return true;
	}
	return false;
}

bool UEObject::HasAnyTags(FGameplayTagContainer Tag, bool ExactMatch) const
{
	return (ExactMatch) ? GameplayTags.HasAnyExact(Tag) : GameplayTags.HasAny(Tag);
}

void UEObject::OnTagAdded_Implementation(FGameplayTag Tag) {}
void UEObject::OnTagRemoved_Implementation(FGameplayTag Tag) {}

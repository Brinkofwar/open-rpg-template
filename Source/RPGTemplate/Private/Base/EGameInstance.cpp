// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EGameInstance.h"

void UEGameInstance::Init()
{
	Super::Init();
	OnInitialized();
}

void UEGameInstance::OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}
void UEGameInstance::OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}

bool UEGameInstance::AddTag(FGameplayTag Tag)
{
	if (!GameplayTags.HasTag(Tag)) {
		GameplayTags.AddTag(Tag);
		OnTagAdded(Tag);
		OnTagAdd.Broadcast(Tag);
		return true;
	}
	return false;
}

bool UEGameInstance::RemoveTag(FGameplayTag Tag)
{
	if (GameplayTags.RemoveTag(Tag)) {
		OnTagRemoved(Tag);
		OnTagRemove.Broadcast(Tag);
		return true;
	}
	return false;
}

bool UEGameInstance::HasAnyTags(FGameplayTagContainer Tag, bool ExactMatch) const
{
	return (ExactMatch) ? GameplayTags.HasAnyExact(Tag) : GameplayTags.HasAny(Tag);
}

void UEGameInstance::OnTagAdded_Implementation(FGameplayTag Tag) {}
void UEGameInstance::OnTagRemoved_Implementation(FGameplayTag Tag) {}
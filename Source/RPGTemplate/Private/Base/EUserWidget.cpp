// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EUserWidget.h"

void UEUserWidget::OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}
void UEUserWidget::OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}

bool UEUserWidget::AddTag(FGameplayTag Tag)
{
	if (!GameplayTags.HasTag(Tag)) {
		GameplayTags.AddTag(Tag);
		OnTagAdded(Tag);
		OnTagAdd.Broadcast(Tag);
		return true;
	}
	return false;
}

bool UEUserWidget::RemoveTag(FGameplayTag Tag)
{
	if (GameplayTags.RemoveTag(Tag)) {
		OnTagRemoved(Tag);
		OnTagRemove.Broadcast(Tag);
		return true;
	}
	return false;
}

bool UEUserWidget::HasAnyTags(FGameplayTagContainer Tag, bool ExactMatch) const
{
	return (ExactMatch) ? GameplayTags.HasAnyExact(Tag) : GameplayTags.HasAny(Tag);
}

void UEUserWidget::OnTagAdded_Implementation(FGameplayTag Tag) {}
void UEUserWidget::OnTagRemoved_Implementation(FGameplayTag Tag) {}
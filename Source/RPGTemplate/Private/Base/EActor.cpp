// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EActor.h"

// Sets default values
AEActor::AEActor()
{

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bStartWithTickEnabled = false;
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEActor::BeginPlay()
{
	
	Super::BeginPlay();
	
}

// Called every frame
void AEActor::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);

}

void AEActor::OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}
void AEActor::OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}

bool AEActor::AddTag(FGameplayTag Tag)
{
	if (!GameplayTags.HasTag(Tag)) {
		GameplayTags.AddTag(Tag);
		OnTagAdded(Tag);
		OnTagAdd.Broadcast(Tag);
		return true;
	}
	return false;
}

bool AEActor::RemoveTag(FGameplayTag Tag)
{
	if (GameplayTags.RemoveTag(Tag)) {
		OnTagRemoved(Tag);
		OnTagRemove.Broadcast(Tag);
		return true;
	}
	return false;
}

bool AEActor::HasAnyTags(FGameplayTagContainer Tag, bool ExactMatch)
{
	return (ExactMatch) ? GameplayTags.HasAnyExact(Tag) : GameplayTags.HasAny(Tag);
}

void AEActor::OnTagAdded_Implementation(FGameplayTag Tag) {}
void AEActor::OnTagRemoved_Implementation(FGameplayTag Tag) {}


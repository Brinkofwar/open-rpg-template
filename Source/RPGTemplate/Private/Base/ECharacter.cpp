// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/ECharacter.h"

// Sets default values
AECharacter::AECharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AECharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AECharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AECharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AECharacter::OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}
void AECharacter::OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}

bool AECharacter::AddTag(FGameplayTag Tag)
{
	if (!GameplayTags.HasTag(Tag)) {
		GameplayTags.AddTag(Tag);
		OnTagAdded(Tag);
		OnTagAdd.Broadcast(Tag);
		return true;
	}
	return false;
}

bool AECharacter::RemoveTag(FGameplayTag Tag)
{
	if (GameplayTags.RemoveTag(Tag)) {
		OnTagRemoved(Tag);
		OnTagRemove.Broadcast(Tag);
		return true;
	}
	return false;
}

bool AECharacter::HasAnyTags(FGameplayTagContainer Tag, bool ExactMatch) const
{
	return (ExactMatch) ? GameplayTags.HasAnyExact(Tag) : GameplayTags.HasAny(Tag);
}

void AECharacter::OnTagAdded_Implementation(FGameplayTag Tag) {}
void AECharacter::OnTagRemoved_Implementation(FGameplayTag Tag) {}

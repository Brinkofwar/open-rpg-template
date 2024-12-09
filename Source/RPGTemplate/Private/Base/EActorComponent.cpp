// Fill out your copyright notice in the Description page of Project Settings.


#include "Base/EActorComponent.h"

// Sets default values for this component's properties
UEActorComponent::UEActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UEActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEActorComponent::SArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters)
{
	CArbitraryRequest(ChannelID, Parameters);
}
bool UEActorComponent::SArbitraryRequest_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters)
{
	return ChannelID.IsValid();
}
void UEActorComponent::CArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters)
{
	OnArbitraryRequest.Broadcast(ChannelID, Parameters);
}
void UEActorComponent::SArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters)
{
	CArbitraryResponse(ChannelID, Parameters);
}
bool UEActorComponent::SArbitraryResponse_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters)
{
	return ChannelID.IsValid();
}
void UEActorComponent::CArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters)
{
	OnArbitraryResponse.Broadcast(ChannelID, Parameters);
}
void UEActorComponent::OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}
void UEActorComponent::OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters) {}



void UEActorComponent::SAddGameplayTag_Implementation(FGameplayTag Tag)
{
	CAddGameplayTag(Tag);
}
bool UEActorComponent::SAddGameplayTag_Validate(FGameplayTag Tag)
{
	return Tag.IsValid();
}
void UEActorComponent::CAddGameplayTag_Implementation(FGameplayTag Tag)
{
	OnTagAdded.Broadcast(Tag);
}
void UEActorComponent::SRemoveGameplayTag_Implementation(FGameplayTag Tag)
{
	CRemoveGameplayTag(Tag);
}
bool UEActorComponent::SRemoveGameplayTag_Validate(FGameplayTag Tag)
{
	return Tag.IsValid();
}
void UEActorComponent::CRemoveGameplayTag_Implementation(FGameplayTag Tag)
{
	OnTagRemoved.Broadcast(Tag);
}

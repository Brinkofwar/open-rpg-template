// Fill out your copyright notice in the Description page of Project Settings.


#include "Component/ReplicatedAction.h"
#include "Net/UnrealNetwork.h"

UReplicatedAction::UReplicatedAction()
{
	SetIsReplicatedByDefault(true);
}

void UReplicatedAction::ServerArbitraryRequest_Implementation(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent)
{
	if (Tag.IsValid()) {
		OnServerArbitraryRequested(Tag, Parameters, isGameEvent);
		ClientArbitraryRequest(Tag, Parameters, isGameEvent);
	}
}

bool UReplicatedAction::ServerArbitraryRequest_Validate(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent)
{
	return Tag.IsValid();
}

void UReplicatedAction::ClientArbitraryRequest_Implementation(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent)
{
	OnClientArbitraryRequested(Tag, Parameters, isGameEvent);
}

void UReplicatedAction::OnServerArbitraryRequested_Implementation(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent)
{
}

void UReplicatedAction::OnClientArbitraryRequested_Implementation(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent)
{
}

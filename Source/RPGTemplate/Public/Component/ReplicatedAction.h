// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/EActorComponent.h"
#include "ReplicatedAction.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UReplicatedAction : public UEActorComponent
{
	GENERATED_BODY()

public:

	UReplicatedAction();

    UFUNCTION(BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "@ServerArbitraryRequest")
    void ServerArbitraryRequest(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent);
    void ServerArbitraryRequest_Implementation(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent);
    bool ServerArbitraryRequest_Validate(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent);

    UFUNCTION(BlueprintCallable, Client, Reliable, DisplayName = "@ClientArbitraryRequest")
    void ClientArbitraryRequest(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent);
    void ClientArbitraryRequest_Implementation(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent);

    UFUNCTION(BlueprintNativeEvent, DisplayName = "@OnServerArbitraryRequested")
    void OnServerArbitraryRequested(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent);
    virtual void OnServerArbitraryRequested_Implementation(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent);

    UFUNCTION(BlueprintNativeEvent, DisplayName = "@OnClientArbitraryRequested")
    void OnClientArbitraryRequested(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent);
    virtual void OnClientArbitraryRequested_Implementation(FGameplayTag Tag, FInstancedStruct Parameters, bool isGameEvent);

};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EActor.generated.h"


UCLASS()
class RPGTEMPLATE_API AEActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEActor();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EActor", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EActor", Meta = (ExposeOnSpawn = true))
	FGameplayTagContainer GameplayTags;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EActor")
	void ArbitraryChannel(FGameplayTagContainer ChannelID, FInstancedStruct Parameters, FGameplayTagContainer &Out_ChannelID, FInstancedStruct &Out_Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EActor")
	void OnArbitraryRequested(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EActor")
	void OnArbitraryResponded(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EActor|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, Category = "EActor|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

};

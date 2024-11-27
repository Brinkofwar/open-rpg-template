// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UEAnimInstance : public UAnimInstance
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EAnimInstance")
	FInstancedStruct Arguments;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EAnimInstance")
	FGameplayTagContainer GameplayTags;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EAnimInstance")
	void ArbitraryChannel(FGameplayTagContainer ChannelID, FInstancedStruct Parameters, FGameplayTagContainer& Out_ChannelID, FInstancedStruct& Out_Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EAnimInstance")
	void OnArbitraryRequested(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EAnimInstance")
	void OnArbitraryResponded(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EActor|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, Category = "EActor|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

};

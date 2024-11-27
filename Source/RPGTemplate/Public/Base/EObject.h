// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RPGTEMPLATE_API UEObject : public UObject
{

	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EObject", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EObject")
	void ArbitraryChannel(FGameplayTagContainer ChannelID, FInstancedStruct Parameters, FGameplayTagContainer& Out_ChannelID, FInstancedStruct& Out_Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EObject")
	void OnArbitraryRequested(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EObject")
	void OnArbitraryResponded(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EObject|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, Category = "EObject|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;


};

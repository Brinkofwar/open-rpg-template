// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UEUserWidget : public UUserWidget
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EUserWidget", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EUserWidget")
	void ArbitraryChannel(FGameplayTagContainer ChannelID, FInstancedStruct Parameters, FGameplayTagContainer& Out_ChannelID, FInstancedStruct& Out_Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EUserWidget")
	void OnArbitraryRequested(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EUserWidget")
	void OnArbitraryResponded(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EUserWidget|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, Category = "EUserWidget|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

};

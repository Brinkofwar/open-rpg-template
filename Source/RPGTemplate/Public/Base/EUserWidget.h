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

#pragma region Properties

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced User Widget", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced User Widget", Meta = (ExposeOnSpawn = true))
	FGameplayTagContainer GameplayTags;

#pragma endregion Properties

#pragma region Arbitrary

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Enhanced User Widget")
	void ArbitraryChannel(FGameplayTag ChannelID, FInstancedStruct Parameters, FGameplayTag& Out_ChannelID, FInstancedStruct& Out_Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced User Widget")
	void OnArbitraryRequested(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced User Widget")
	void OnArbitraryResponded(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Enhanced User Widget|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced User Widget|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

#pragma endregion Arbitrary

#pragma region GameplayTags

	UFUNCTION(BlueprintCallable, Category = "Enhanced User Widget|Gameplay Tag")
	bool AddTag(FGameplayTag Tag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced User Widget|Gameplay Tag")
	void OnTagAdded(FGameplayTag Tag);
	virtual void OnTagAdded_Implementation(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Enhanced User Widget|Gameplay Tag")
	bool RemoveTag(FGameplayTag Tag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced User Widget|Gameplay Tag")
	void OnTagRemoved(FGameplayTag Tag);
	virtual void OnTagRemoved_Implementation(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enhanced User Widget|Gameplay Tag")
	bool HasAnyTags(FGameplayTagContainer Tag, bool ExactMatch) const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagAdd, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced User Widget|Event Dispatcher")
	FOnTagAdd OnTagAdd;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagRemove, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced User Widget|Event Dispatcher")
	FOnTagRemove OnTagRemove;

#pragma endregion GameplayTags

};

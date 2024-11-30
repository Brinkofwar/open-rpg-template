// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UEGameInstance : public UGameInstance
{

	GENERATED_BODY()

public:

	virtual void Init() override;

protected:

	UFUNCTION(BlueprintImplementableEvent)
	void OnInitialized();

public:


#pragma region Properties

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enhanced Game Instance", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enhanced Game Instance", Meta = (ExposeOnSpawn = true))
	FGameplayTagContainer GameplayTags;

#pragma endregion Properties

#pragma region Arbitrary

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Enhanced Game Instance")
	void ArbitraryChannel(FGameplayTag ChannelID, FInstancedStruct Parameters, FGameplayTag& Out_ChannelID, FInstancedStruct& Out_Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced Game Instance")
	void OnArbitraryRequested(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced Game Instance")
	void OnArbitraryResponded(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Enhanced Game Instance|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Enhanced Game Instance|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

#pragma endregion Arbitrary

#pragma region GameplayTags

	UFUNCTION(BlueprintCallable, Category = "Enhanced Game Instance|Gameplay Tag")
	bool AddTag(FGameplayTag Tag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced Game Instance|Gameplay Tag")
	void OnTagAdded(FGameplayTag Tag);
	virtual void OnTagAdded_Implementation(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, Category = "Enhanced Game Instance|Gameplay Tag")
	bool RemoveTag(FGameplayTag Tag);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Enhanced Game Instance|Gameplay Tag")
	void OnTagRemoved(FGameplayTag Tag);
	virtual void OnTagRemoved_Implementation(FGameplayTag Tag);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Enhanced Game Instance|Gameplay Tag")
	bool HasAnyTags(FGameplayTagContainer Tag, bool ExactMatch) const;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagAdd, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced Game Instance|Event Dispatcher")
	FOnTagAdd OnTagAdd;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagRemove, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced Game Instance|Event Dispatcher")
	FOnTagRemove OnTagRemove;

#pragma endregion GameplayTags


};

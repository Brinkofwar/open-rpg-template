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
UCLASS(DisplayName = "Extended Anim Instance")
class RPGTEMPLATE_API UEAnimInstance : public UAnimInstance
{

	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Extended Anim Instance", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;

#pragma region Arbitrary

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Extended Anim Instance")
	void ArbitraryChannel(FGameplayTag ChannelID, FInstancedStruct Parameters, FGameplayTag& Out_ChannelID, FInstancedStruct& Out_Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Extended Anim Instance")
	void OnArbitraryRequested(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Extended Anim Instance")
	void OnArbitraryResponded(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Extended Anim Instance|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Extended Anim Instance|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

#pragma endregion Arbitrary

};

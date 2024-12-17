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
UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew, CollapseCategories, DisplayName = "Extended Object")
class RPGTEMPLATE_API UEObject : public UObject
{

	GENERATED_BODY()

public:

	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Extended Object", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;

#pragma region Arbitrary

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Extended Object")
	void ArbitraryChannel(FGameplayTag ChannelID, FInstancedStruct Parameters, FGameplayTag& Out_ChannelID, FInstancedStruct& Out_Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Extended Object")
	void OnArbitraryRequested(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Extended Object")
	void OnArbitraryResponded(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Extended Object|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Extended Object|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

#pragma endregion Arbitrary

};

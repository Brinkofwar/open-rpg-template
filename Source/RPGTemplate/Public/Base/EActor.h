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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Enhanced Actor", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region Arbitrary

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Arbitrary Request", Category = "Enhanced Actor|Arbitrary")
	void SArbitraryRequest(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void SArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);
	bool SArbitraryRequest_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(NetMulticast, Reliable)
	void CArbitraryRequest(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void CArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Arbitrary Response", Category = "Enhanced Actor|Arbitrary")
	void SArbitraryResponse(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void SArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);
	bool SArbitraryResponse_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(NetMulticast, Reliable)
	void CArbitraryResponse(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void CArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, BlueprintCallable, Category = "Enhanced Actor|Arbitrary")
	void ArbitraryChannel(FGameplayTag ChannelID, FInstancedStruct Parameters, FGameplayTag& Out_ChannelID, FInstancedStruct& Out_Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, BlueprintCallable, Category = "Enhanced Actor|Arbitrary")
	void OnArbitraryRequested(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, BlueprintCallable, Category = "Enhanced Actor|Arbitrary")
	void OnArbitraryResponded(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Enhanced Actor|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Enhanced Actor|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

#pragma endregion Arbitrary

#pragma region GameplayTag

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Enhanced Actor", Meta = (ExposeOnSpawn = true))
	FGameplayTagContainer GameplayTags;

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Add Local Gameplay Tag", Category = "Enhanced Actor|Gameplay Tag")
	void SAddGameplayTag(FGameplayTag Tag);
	void SAddGameplayTag_Implementation(FGameplayTag Tag);
	bool SAddGameplayTag_Validate(FGameplayTag Tag);

	UFUNCTION(NetMulticast, Reliable)
	void CAddGameplayTag(FGameplayTag Tag);
	void CAddGameplayTag_Implementation(FGameplayTag Tag);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Remove Local Gameplay Tag", Category = "Enhanced Actor|Gameplay Tag")
	void SRemoveGameplayTag(FGameplayTag Tag);
	void SRemoveGameplayTag_Implementation(FGameplayTag Tag);
	bool SRemoveGameplayTag_Validate(FGameplayTag Tag);

	UFUNCTION(NetMulticast, Reliable)
	void CRemoveGameplayTag(FGameplayTag Tag);
	void CRemoveGameplayTag_Implementation(FGameplayTag Tag);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagAdded, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced Actor|Event Dispatcher")
	FOnTagAdded OnTagAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagRemoved, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Enhanced Actor|Event Dispatcher")
	FOnTagRemoved OnTagRemoved;

#pragma endregion GameplayTag

};

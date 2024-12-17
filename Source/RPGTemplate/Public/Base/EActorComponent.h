// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EActorComponent.generated.h"


UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), DisplayName = "Extended Actor Component")
class RPGTEMPLATE_API UEActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEActorComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated, Category = "Extended Actor Component", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

#pragma region Arbitrary

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Arbitrary Request", Category = "Extended Actor Component")
	void SArbitraryRequest(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void SArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);
	bool SArbitraryRequest_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(NetMulticast, Reliable)
	void CArbitraryRequest(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void CArbitraryRequest_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Arbitrary Response", Category = "Extended Actor Component")
	void SArbitraryResponse(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void SArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);
	bool SArbitraryResponse_Validate(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(NetMulticast, Reliable)
	void CArbitraryResponse(FGameplayTag ChannelID, FInstancedStruct Parameters);
	void CArbitraryResponse_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCosmetic, BlueprintCallable, Category = "Extended Actor Component")
	void ArbitraryChannel(FGameplayTag ChannelID, FInstancedStruct Parameters, FGameplayTag& Out_ChannelID, FInstancedStruct& Out_Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, BlueprintCallable, Category = "Extended Actor Component")
	void OnArbitraryRequested(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryRequested_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	UFUNCTION(BlueprintNativeEvent, BlueprintCosmetic, BlueprintCallable, Category = "Extended Actor Component")
	void OnArbitraryResponded(FGameplayTag ChannelID, FInstancedStruct Parameters);
	virtual void OnArbitraryResponded_Implementation(FGameplayTag ChannelID, FInstancedStruct Parameters);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Extended Actor Component|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTag, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "Extended Actor Component|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;

#pragma endregion Arbitrary

#pragma region GameplayTag

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = "Extended Actor Component", Meta = (ExposeOnSpawn = true))
	FGameplayTagContainer GameplayTags;

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Add Gameplay Tag", Category = "Extended Actor Component|Gameplay Tag")
	void SAddGameplayTag(FGameplayTag Tag);
	void SAddGameplayTag_Implementation(FGameplayTag Tag);
	bool SAddGameplayTag_Validate(FGameplayTag Tag);

	UFUNCTION(NetMulticast, Reliable)
	void CAddGameplayTag(FGameplayTag Tag);
	void CAddGameplayTag_Implementation(FGameplayTag Tag);


	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable, Server, Reliable, WithValidation, DisplayName = "Remove Gameplay Tag", Category = "Extended Actor Component|Gameplay Tag")
	void SRemoveGameplayTag(FGameplayTag Tag);
	void SRemoveGameplayTag_Implementation(FGameplayTag Tag);
	bool SRemoveGameplayTag_Validate(FGameplayTag Tag);

	UFUNCTION(NetMulticast, Reliable)
	void CRemoveGameplayTag(FGameplayTag Tag);
	void CRemoveGameplayTag_Implementation(FGameplayTag Tag);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagAdded, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Extended Actor Component|Event Dispatcher")
	FOnTagAdded OnTagAdded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagRemoved, FGameplayTag, Tag);
	UPROPERTY(BlueprintAssignable, Category = "Extended Actor Component|Event Dispatcher")
	FOnTagRemoved OnTagRemoved;

#pragma endregion GameplayTag
		
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "EActorComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "EActorComponent", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EActorComponent", Meta = (ExposeOnSpawn = true))
	FGameplayTagContainer GameplayTags;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "EActorComponent")
	void ArbitraryChannel(FGameplayTagContainer ChannelID, FInstancedStruct Parameters, FGameplayTagContainer& Out_ChannelID, FInstancedStruct& Out_Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EActorComponent")
	void OnArbitraryRequested(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "EActorComponent")
	void OnArbitraryResponded(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EActorComponent|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, Category = "EActorComponent|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};

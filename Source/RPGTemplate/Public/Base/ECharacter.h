// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"
#include "InstancedStruct.h"
#include "ECharacter.generated.h"

UCLASS()
class RPGTEMPLATE_API AECharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AECharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ECharacter", Meta = (ExposeOnSpawn = true))
	FInstancedStruct Arguments;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ECharacter", Meta = (ExposeOnSpawn = true))
	FGameplayTagContainer GameplayTags;


	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "ECharacter")
	void ArbitraryChannel(FGameplayTagContainer ChannelID, FInstancedStruct Parameters, FGameplayTagContainer& Out_ChannelID, FInstancedStruct& Out_Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "ECharacter")
	void OnArbitraryRequested(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	UFUNCTION(BlueprintImplementableEvent, Category = "ECharacter")
	void OnArbitraryResponded(FGameplayTagContainer ChannelID, FInstancedStruct Parameters);


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryRequest, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "ECharacter|Event Dispatcher")
	FOnArbitraryRequest OnArbitraryRequest;


	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnArbitraryResponse, FGameplayTagContainer, ChannelID, FInstancedStruct, Parameters);
	UPROPERTY(BlueprintAssignable, Category = "ECharacter|Event Dispatcher")
	FOnArbitraryResponse OnArbitraryResponse;


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

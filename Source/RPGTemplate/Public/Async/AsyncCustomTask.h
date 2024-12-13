// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "InstancedStruct.h"
#include "Base/EObject.h"
#include "AsyncCustomTask.generated.h"


/**
 *
 */
UCLASS(Blueprintable)
class RPGTEMPLATE_API UAsyncTaskObject : public UEObject
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Async Task Object")
	void StartTask();

	UFUNCTION(BlueprintCallable, Category = "Async Task Object")
	void EndTask(bool IsSuccess);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Async Task Object")
	void OnStart();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStarted);
	UPROPERTY(BlueprintAssignable)
	FOnStarted OnStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnded, bool, IsSuccess);
	UPROPERTY(BlueprintAssignable)
	FOnEnded OnEnded;

};


/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UAsyncCustomTask : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Async Custom Task", meta = (BlueprintInternalUseOnly = "true", DefaultToSelf = "Outer"))
	static UAsyncCustomTask* Start(TSubclassOf<UAsyncTaskObject> ActionClass, FInstancedStruct Arguments, UObject* Outer, float Timeout = 10.0f);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStarted, UObject*, Object);
	UPROPERTY(BlueprintAssignable, DisplayName = "Started")
	FOnStarted OnStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSuccess, UObject*, Object);
	UPROPERTY(BlueprintAssignable, DisplayName = "Success")
	FOnSuccess OnSuccess;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnError, UObject*, Object);
	UPROPERTY(BlueprintAssignable, DisplayName = "Error")
	FOnError OnError;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTimeout, UObject*, Object);
	UPROPERTY(BlueprintAssignable, DisplayName = "Timeout")
	FOnTimeout OnTimeout;

private:

	FTimerHandle TimeoutHandle;
	float TimeoutDuration = 10.0f;

	UFUNCTION()
	void HandleTimeout();

	UFUNCTION()
	void HandleTaskStarted();

	UFUNCTION()
	void HandleTaskEnded(bool IsSuccess);

	void EndTask();

	UPROPERTY()
	UAsyncTaskObject* TaskObject;

	UPROPERTY()
	UWorld* World;

};

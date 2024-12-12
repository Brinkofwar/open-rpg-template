// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Base/EObject.h"
#include "AsyncTaskObject.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RPGTEMPLATE_API UAsyncTaskObject : public UEObject
{

	GENERATED_BODY()

public:

	void StartTask();

	UFUNCTION(BlueprintCallable, Category = "Async Task Object")
	void EndTask(bool IsSuccess);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Async Task Object")
	void OnStart();

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStarted);
	UPROPERTY(BlueprintAssignable)
	FOnStarted OnStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnded, bool, Success);
	UPROPERTY(BlueprintAssignable)
	FOnEnded OnEnded;

};

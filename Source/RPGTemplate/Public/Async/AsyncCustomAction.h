// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "RPGTemplate/Public/Async/AsyncTaskObject.h"
#include "InstancedStruct.h"
#include "AsyncCustomAction.generated.h"

/**
 * 
 */
UCLASS()
class RPGTEMPLATE_API UAsyncCustomAction : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, DisplayName = "Async Custom Action", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncCustomAction* Start(TSubclassOf<UAsyncTaskObject> ActionClass, FInstancedStruct Arguments, UObject* Outer);

	virtual void Activate() override;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStarted, UObject*, ActionObject);
	UPROPERTY(BlueprintAssignable, DisplayName = "Started")
	FOnStarted OnStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnded, UObject*, ActionObject);
	UPROPERTY(BlueprintAssignable, DisplayName = "Ended")
	FOnEnded OnEnded;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnError, UObject*, ActionObject);
	UPROPERTY(BlueprintAssignable, DisplayName = "Error")
	FOnError OnError;

private:

	UFUNCTION()
	void HandleTaskStarted();

	UFUNCTION()
	void HandleTaskEnded(bool IsSuccess);

	void EndTask();

	UPROPERTY()
	UAsyncTaskObject* ActionObject;

};

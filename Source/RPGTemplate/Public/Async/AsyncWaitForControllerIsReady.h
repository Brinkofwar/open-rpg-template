// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncWaitForControllerIsReady.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnControllerChanged, AController*, OldController, AController*, NewController);

/**
 * 
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class RPGTEMPLATE_API UAsyncWaitForControllerIsReady : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnControllerChanged OnControllerChanged;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncWaitForControllerIsReady* WaitForControllerIsReady(APawn* TargetPawn);

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	APawn* TargetPawn;

	UFUNCTION()
	void HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);

};

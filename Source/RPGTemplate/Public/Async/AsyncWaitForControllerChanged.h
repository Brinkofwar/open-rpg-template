// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AsyncWaitForControllerChanged.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class RPGTEMPLATE_API UAsyncWaitForControllerChanged : public UBlueprintAsyncActionBase
{

	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnControllerChanged, AController*, OldController, AController*, NewController);
	UPROPERTY(BlueprintAssignable, DisplayName="Changed")
	FOnControllerChanged OnControllerChanged;

	UFUNCTION(BlueprintCallable, DisplayName = "Async Wait For Controller Changed", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncWaitForControllerChanged* Start(APawn* TargetPawn);

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	APawn* TargetPawn;

	UFUNCTION()
	void HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController);

};

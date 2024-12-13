// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "AsyncWaitForInputAction.generated.h"


/**
 * 
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class RPGTEMPLATE_API UAsyncWaitForInputAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionTriggerDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);
	UPROPERTY(BlueprintAssignable)
	FInputActionTriggerDelegate OnTriggered;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionStartDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);
	UPROPERTY(BlueprintAssignable)
	FInputActionStartDelegate OnStarted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionOngoingDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);
	UPROPERTY(BlueprintAssignable)
	FInputActionOngoingDelegate OnGoing;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionCompleteDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);
	UPROPERTY(BlueprintAssignable)
	FInputActionCompleteDelegate OnCompleted;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionCancelDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);
	UPROPERTY(BlueprintAssignable)
	FInputActionCancelDelegate OnCanceled;

	UFUNCTION(BlueprintCallable, DisplayName = "Async Wait For Input Action", meta = (BlueprintInternalUseOnly = "true"))
	static UAsyncWaitForInputAction* Start(UEnhancedInputComponent* InputComponent, UInputAction* Action);

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable)
	void EndTask();

protected:

	UInputAction* InputAction;
	UEnhancedInputComponent* EnhancedInputComponent;

	FInputBindingHandle* InputHandleCancel;
	FInputBindingHandle* InputHandleComplete;
	FInputBindingHandle* InputHandleOngoing;
	FInputBindingHandle* InputHandleStart;
	FInputBindingHandle* InputHandleTrigger;

	void HandleInputActionTrigger(const FInputActionInstance& ActionInstance);
	void HandleInputActionCancel(const FInputActionInstance& ActionInstance);
	void HandleInputActionOngoing(const FInputActionInstance& ActionInstance);
	void HandleInputActionComplete(const FInputActionInstance& ActionInstance);
	void HandleInputActionStart(const FInputActionInstance& ActionInstance);


};

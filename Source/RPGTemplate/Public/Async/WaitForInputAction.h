// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "WaitForInputAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionTriggerDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionCancelDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionOngoingDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionCompleteDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FInputActionStartDelegate, const FInputActionValue&, InputValue, float, Elapsed, float, Triggered);

/**
 * 
 */
UCLASS(BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class RPGTEMPLATE_API UWaitForInputAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FInputActionTriggerDelegate OnTriggered;

	UPROPERTY(BlueprintAssignable)
	FInputActionStartDelegate OnStarted;

	UPROPERTY(BlueprintAssignable)
	FInputActionOngoingDelegate OnGoing;

	UPROPERTY(BlueprintAssignable)
	FInputActionCompleteDelegate OnCompleted;

	UPROPERTY(BlueprintAssignable)
	FInputActionCancelDelegate OnCanceled;

	UFUNCTION(BlueprintCallable, Category = "Async Input", meta = (BlueprintInternalUseOnly = "true"))
	static UWaitForInputAction* ListenForInputAction(UEnhancedInputComponent* InputComponent, UInputAction* Action);

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, Category = "Input|Async")
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

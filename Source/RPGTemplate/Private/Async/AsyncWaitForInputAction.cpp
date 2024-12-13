// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncWaitForInputAction.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Library/UtilityLibrary.h"
#include "EnhancedInputComponent.h"

UAsyncWaitForInputAction* UAsyncWaitForInputAction::Start(UEnhancedInputComponent* InputComponent, UInputAction* Action)
{
    UAsyncWaitForInputAction* task = NewObject<UAsyncWaitForInputAction>();
    task->EnhancedInputComponent = InputComponent;
    task->InputAction = Action;
    return task;
}

void UAsyncWaitForInputAction::Activate()
{
    if (!EnhancedInputComponent || !InputAction)
    {
        return;
    }

    InputHandleCancel = &EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Canceled, this, &UAsyncWaitForInputAction::HandleInputActionCancel);
    InputHandleComplete = &EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Completed, this, &UAsyncWaitForInputAction::HandleInputActionComplete);
    InputHandleOngoing = &EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Ongoing, this, &UAsyncWaitForInputAction::HandleInputActionOngoing);
    InputHandleStart = &EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Started, this, &UAsyncWaitForInputAction::HandleInputActionStart);
    InputHandleTrigger = &EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &UAsyncWaitForInputAction::HandleInputActionTrigger);

    //EnhancedInputComponent->RemoveBinding(*Actions);

    // EnhancedInputComponent->RemoveActionBindingForHandle(han.GetHandle());
    // EnhancedInputComponent->RemoveActionEventBinding(han.GetHandle());

    //const TArray<TUniquePtr<FEnhancedInputActionEventBinding>>& bdns = EnhancedInputComponent->GetActionEventBindings();

    //// GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Cyan, FString::FromInt(bdns.Num()));
    //for (int i = 0; i < bdns.Num(); i++) {

    //    GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Cyan, bdns[i].Get()->GetAction()->GetFullName());
    //    if (bdns[i].Get()->GetAction() == InputAction) {
    //        GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Red, FString::FromInt(i));
    //        EnhancedInputComponent->RemoveActionEventBinding(i);
    //    }

    //}

    /*for (int i = 0; i < 5; i++) {

        const bool x = EnhancedInputComponent->RemoveActionEventBinding(i);
        if (x) {
            GEngine->AddOnScreenDebugMessage(-1, 30.0f, FColor::Cyan, FString::FromInt(i));
        }

    }*/
    

}

void UAsyncWaitForInputAction::HandleInputActionCancel(const FInputActionInstance& ActionInstance)
{
    if (OnCanceled.IsBound())
    {
        OnCanceled.Broadcast(ActionInstance.GetValue(), ActionInstance.GetElapsedTime(), ActionInstance.GetTriggeredTime());
    }
}
void UAsyncWaitForInputAction::HandleInputActionComplete(const FInputActionInstance& ActionInstance)
{
    if (OnCompleted.IsBound())
    {
        OnCompleted.Broadcast(ActionInstance.GetValue(), ActionInstance.GetElapsedTime(), ActionInstance.GetTriggeredTime());
    }
}
void UAsyncWaitForInputAction::HandleInputActionOngoing(const FInputActionInstance& ActionInstance)
{
    if (OnGoing.IsBound())
    {
        OnGoing.Broadcast(ActionInstance.GetValue(), ActionInstance.GetElapsedTime(), ActionInstance.GetTriggeredTime());
    }
}
void UAsyncWaitForInputAction::HandleInputActionStart(const FInputActionInstance& ActionInstance)
{
    if (OnStarted.IsBound())
    {
        OnStarted.Broadcast(ActionInstance.GetValue(), ActionInstance.GetElapsedTime(), ActionInstance.GetTriggeredTime());
    }
}
void UAsyncWaitForInputAction::HandleInputActionTrigger(const FInputActionInstance& ActionInstance)
{
    if (OnTriggered.IsBound())
    {
        OnTriggered.Broadcast(ActionInstance.GetValue(), ActionInstance.GetElapsedTime(), ActionInstance.GetTriggeredTime());
    }
}

void UAsyncWaitForInputAction::EndTask()
{
    if (EnhancedInputComponent && InputAction)
    {
        EnhancedInputComponent->RemoveBinding(*InputHandleCancel);
        EnhancedInputComponent->RemoveBinding(*InputHandleComplete);
        EnhancedInputComponent->RemoveBinding(*InputHandleOngoing);
        EnhancedInputComponent->RemoveBinding(*InputHandleStart);
        EnhancedInputComponent->RemoveBinding(*InputHandleTrigger);

        EnhancedInputComponent = nullptr;

        InputHandleCancel = nullptr;
        InputHandleComplete = nullptr;
        InputHandleOngoing = nullptr;
        InputHandleStart = nullptr;
        InputHandleTrigger = nullptr;
    }
    if (IsValid(this))
    {
        SetReadyToDestroy();
        MarkAsGarbage();
    }
}

// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncWaitForControllerChanged.h"

UAsyncWaitForControllerChanged* UAsyncWaitForControllerChanged::Start(APawn* Pawn)
{
    UAsyncWaitForControllerChanged* task = NewObject<UAsyncWaitForControllerChanged>();
    task->TargetPawn = Pawn;
    return task;
}

void UAsyncWaitForControllerChanged::Activate()
{
    if (TargetPawn) {
        TargetPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &UAsyncWaitForControllerChanged::HandleControllerChanged);
    }
}

void UAsyncWaitForControllerChanged::HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController)
{
    OnControllerChanged.Broadcast(OldController, NewController);
}

void UAsyncWaitForControllerChanged::EndTask()
{
    if (TargetPawn)
    {
        TargetPawn->ReceiveControllerChangedDelegate.RemoveDynamic(this, &UAsyncWaitForControllerChanged::HandleControllerChanged);
        TargetPawn = nullptr;
    }
    if (IsValid(this))
    {
        SetReadyToDestroy();
        MarkAsGarbage();
    }
}

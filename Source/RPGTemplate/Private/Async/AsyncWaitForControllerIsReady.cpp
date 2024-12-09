// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncWaitForControllerIsReady.h"

UAsyncWaitForControllerIsReady* UAsyncWaitForControllerIsReady::WaitForControllerIsReady(APawn* Pawn)
{
    UAsyncWaitForControllerIsReady* task = NewObject<UAsyncWaitForControllerIsReady>();
    task->TargetPawn = Pawn;
    return task;
}

void UAsyncWaitForControllerIsReady::Activate()
{
    if (TargetPawn) {
        TargetPawn->ReceiveControllerChangedDelegate.AddDynamic(this, &UAsyncWaitForControllerIsReady::HandleControllerChanged);
    }
}

void UAsyncWaitForControllerIsReady::HandleControllerChanged(APawn* Pawn, AController* OldController, AController* NewController)
{
    OnControllerChanged.Broadcast(OldController, NewController);
}

void UAsyncWaitForControllerIsReady::EndTask()
{
    if (TargetPawn)
    {
        TargetPawn->ReceiveControllerChangedDelegate.RemoveDynamic(this, &UAsyncWaitForControllerIsReady::HandleControllerChanged);
        TargetPawn = nullptr;
    }
    SetReadyToDestroy();
}

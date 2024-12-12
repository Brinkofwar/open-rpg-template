// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncCustomAction.h"
#include "RPGTemplate/Public/Async/AsyncTaskObject.h"

UAsyncCustomAction* UAsyncCustomAction::Start(TSubclassOf<UAsyncTaskObject> ActionClass, FInstancedStruct Arguments, UObject* Outer)
{
    if (!ActionClass || !ActionClass->IsChildOf(UAsyncTaskObject::StaticClass()))
    {
        return nullptr;
    }

    UAsyncCustomAction* task = NewObject<UAsyncCustomAction>();
    task->ActionObject = NewObject<UAsyncTaskObject>((Outer) ? Outer : task, ActionClass);
    task->ActionObject->OnStarted.AddDynamic(task, &UAsyncCustomAction::HandleTaskStarted);
    task->ActionObject->OnEnded.AddDynamic(task, &UAsyncCustomAction::HandleTaskEnded);

    if (Arguments.IsValid()) {
        task->ActionObject->Arguments = Arguments;
    }

    return task;
}

void UAsyncCustomAction::Activate()
{
    if (ActionObject)
    {
        ActionObject->StartTask();
    }
    else {
        EndTask();
    }
}

void UAsyncCustomAction::HandleTaskStarted()
{
    OnStarted.Broadcast(ActionObject);
}

void UAsyncCustomAction::HandleTaskEnded(bool IsSuccess)
{
    if (IsSuccess) {
        OnEnded.Broadcast(ActionObject);
    }
    else {
        OnError.Broadcast(ActionObject);
    }
    EndTask();
}

void UAsyncCustomAction::EndTask()
{
    if (IsValid(this))
    {
        SetReadyToDestroy();
    }
}

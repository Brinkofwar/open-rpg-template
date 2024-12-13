// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncCustomTask.h"



void UAsyncTaskObject::StartTask()
{
    OnStart();
    OnStarted.Broadcast();
}

void UAsyncTaskObject::EndTask(bool IsSuccess)
{
    OnEnded.Broadcast(IsSuccess);
}



UAsyncCustomTask* UAsyncCustomTask::Start(TSubclassOf<UAsyncTaskObject> ActionClass, FInstancedStruct Arguments, UObject* Outer, float Timeout)
{
    if (!ActionClass || !ActionClass->IsChildOf(UAsyncTaskObject::StaticClass()) || Timeout <= 0)
    {
        return nullptr;
    }

    if (!IsValid(Outer) && !IsValid(Outer->GetWorld()))
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid Outer object passed to UAsyncCustomTask::Start"));
        return nullptr;
    }

    UAsyncCustomTask* task = NewObject<UAsyncCustomTask>();
    task->TimeoutDuration = Timeout;
    task->World = Outer->GetWorld();

    task->TaskObject = NewObject<UAsyncTaskObject>(Outer, ActionClass);
    task->TaskObject->OnStarted.AddDynamic(task, &UAsyncCustomTask::HandleTaskStarted);
    task->TaskObject->OnEnded.AddDynamic(task, &UAsyncCustomTask::HandleTaskEnded);

    if (Arguments.IsValid()) {
        task->TaskObject->Arguments = Arguments;
    }

    return task;
}

void UAsyncCustomTask::Activate()
{
    if (IsValid(TaskObject) && IsValid(World))
    {

        TaskObject->StartTask();
        World->GetTimerManager().SetTimer(TimeoutHandle, this, &UAsyncCustomTask::HandleTimeout, TimeoutDuration, false);

    }
    else {
        EndTask();
    }
}

void UAsyncCustomTask::HandleTimeout()
{
    OnTimeout.Broadcast(TaskObject);
    EndTask();
}

void UAsyncCustomTask::HandleTaskStarted()
{
    OnStarted.Broadcast(TaskObject);
}

void UAsyncCustomTask::HandleTaskEnded(bool IsSuccess)
{
    if (IsSuccess) {
        OnSuccess.Broadcast(TaskObject);
    }
    else {
        OnError.Broadcast(TaskObject);
    }
    EndTask();
}

void UAsyncCustomTask::EndTask()
{
    if (IsValid(World)) {
        World->GetTimerManager().ClearTimer(TimeoutHandle);
    }

    if (IsValid(this))
    {
        SetReadyToDestroy();
        MarkAsGarbage();
    }
}

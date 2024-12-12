// Fill out your copyright notice in the Description page of Project Settings.


#include "Async/AsyncTaskObject.h"

void UAsyncTaskObject::StartTask()
{
	OnStart();
	OnStarted.Broadcast();
}

void UAsyncTaskObject::EndTask(bool IsSuccess)
{
	OnEnded.Broadcast(IsSuccess);
}

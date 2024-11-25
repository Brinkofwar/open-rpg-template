// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ELogType.generated.h"

UENUM(BlueprintType)
enum ELogType {
	Message UMETA(DisplayName = "Message"),
	Success UMETA(DisplayName = "Success"),
	Warning UMETA(DisplayName="Warning"),
	Error UMETA(DisplayName = "Error")
};
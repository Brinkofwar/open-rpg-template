// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EBranchType.generated.h"

UENUM(BlueprintType)
enum EBranchType {
	OnTrue UMETA(DisplayName = "OnTrue"),
	OnFalse UMETA(DisplayName = "OnFalse")
};